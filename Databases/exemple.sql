--EX 12.
--Pentru fiecare client, afisati numarul de plati efectuate.
SELECT
    c.ID_CLIENT,
    (
        select COUNT(p.id_plata)
        from PLATA p
        where
            c.ID_CLIENT = p.ID_CLIENT
        ) AS NUMAR_PLATI
FROM
     CLIENT c;

--Afișați un raport despre clienți, pachetele turistice pe care le-au cumpărat și date despre angajații care
-- au gestionat contractele pentru acele vânzări.
-- Raportul va include suma totală a plăților efectuate de fiecare client și numele angajatului responsabil.
WITH PLATA_CLIENT AS (
    SELECT
        c.id_client,
        c.nume AS Nume_Client,
        c.prenume AS Prenume_Client,
        SUM(p.suma_platita) AS Total_Platit
    FROM
        CLIENT c
    JOIN
        PLATA p ON c.id_client = p.id_client
    GROUP BY
        c.id_client, c.nume, c.prenume
),
DETALII_CONTRACT AS (
    SELECT
        co.id_contract,
        co.id_client,
        co.id_angajat
    FROM
        CONTRACT co
),
DETALII_ANGAJAT AS (
    SELECT
        a.id_angajat,
        a.nume AS Nume_Angajat,
        COUNT(dc.id_contract) AS Numar_Contracte,
        SUM(pc.Total_Platit) AS Venituri_Generate
    FROM
        ANGAJAT a
    JOIN
        DETALII_CONTRACT dc ON a.id_angajat = dc.id_angajat
    JOIN
        PLATA_CLIENT pc ON dc.id_client = pc.id_client
    GROUP BY
        a.id_angajat, a.nume
)
SELECT
    pc.Nume_Client,
    pc.Prenume_Client,
    pc.Total_Platit,
    da.Nume_Angajat,
    da.Numar_Contracte,
    da.Venituri_Generate
FROM
    PLATA_CLIENT pc
JOIN
    DETALII_CONTRACT dc ON pc.id_client = dc.id_client
JOIN
    DETALII_ANGAJAT da ON dc.id_angajat = da.id_angajat
ORDER BY
    da.Venituri_Generate DESC;





--Afișați toate hotelurile care apartin unui pachet turistic cu un venit total, mai mare decât suma medie platita de clienti, din rezervări
--de pachete turistice, incluzând numărul total de rezervări făcute pentru fiecare hotel,
--precum și venitul mediu per pachet turistic.

SELECT
    h.nume AS nume_hotel,
    COUNT(pt.id_oferta) AS numar_rezervari,
    AVG(pt.pret) AS venit_mediu_pachet,
    SUM(pt.pret) AS venit_total
FROM
    HOTEL h
JOIN
    PACHET_TURISTIC pt ON h.id_hotel = pt.id_hotel
GROUP BY
    h.nume
HAVING
    SUM(pt.pret) > (
        select AVG(p.SUMA_PLATITA)
        from PLATA p
        join CLIENT c ON c.ID_CLIENT=p.ID_CLIENT
        )
ORDER BY
    venit_total DESC;

--Afișați o listă a tuturor clienților și pachetelor turistice pe care le-au achiziționat, incluzând tipul de vehicul
--pentru transport și numele hotelului, împreună cu suma plătită, interpretând metoda de plată într-un format mai clar.

SELECT
    c.nume AS Nume_Client,
    c.prenume AS Prenume_Client,
    NVL(c.email, 'Email nespecificat') AS Email_Client,
    pt.destinatia AS Destinatie_Pachet,
    pt.pret AS Pret_Pachet,
    NVL(t.tip_vehicul, 'Tip vehicul nespecificat') AS Tip_Vehicul,
    h.nume AS Nume_Hotel,
    DECODE(p.metoda_plata, 'card', 'Plată cu cardul', 'cash', 'Plată în numerar', 'Metodă de plată nespecificată') AS Metoda_Platii,
    NVL(p.suma_platita, 0) AS Suma_Platita
FROM
    CLIENT c
left JOIN
    DELIMITARE d ON c.id_client = d.id_client
left JOIN
    PACHET_TURISTIC pt ON d.id_oferta = pt.id_oferta
LEFT JOIN
    TRANSPORT t ON pt.id_transport = t.id_transport
LEFT JOIN
    HOTEL h ON pt.id_hotel = h.id_hotel
LEFT JOIN
    PLATA p ON c.id_client = p.id_client
ORDER BY
    c.nume, c.prenume;


--Afișați datele personale ale clientului și detalii ale ultimului pachet turistic achiziționat.
--Data estimată a întoarcerii și diferența în zile dintre data plecării și data întoarcerii.
--Statusul achitării, interpretând metoda de plată.
--Numele și prenumele angajatului responsabil pentru contractul clientului, cu numele de familie în majuscule.

SELECT
    c.nume AS Nume_Client,
    c.prenume AS Prenume_Client,
    UPPER(a.prenume || ' ' || UPPER(a.nume)) AS Nume_Angajat,
    pt.destinatia AS Destinatia,
    TO_CHAR(pt.data_plecare, 'DD-MON-YYYY') AS Data_Plecare,
    TO_CHAR(pt.data_intoarcere, 'DD-MON-YYYY') AS Data_Intoarcere,
    pt.data_intoarcere - pt.data_plecare AS Durata_Zile,
    CASE
        WHEN p.metoda_plata = 'card' THEN 'Plătit cu cardul'
        WHEN p.metoda_plata = 'cash' THEN 'Plătit în numerar'
        WHEN p.metoda_plata = 'online' THEN 'Plătit online'
        ELSE 'Metodă de plată necunoscută'
    END AS Status_Plata
FROM
    CLIENT c
JOIN
    DELIMITARE d ON c.id_client = d.id_client
JOIN
    PACHET_TURISTIC pt ON d.id_oferta = pt.id_oferta
JOIN
    CONTRACT co ON c.id_client = co.id_client
JOIN
    ANGAJAT a ON co.id_angajat = a.id_angajat
JOIN
    PLATA p ON c.id_client = p.id_client
WHERE
    pt.id_oferta = (
        SELECT MAX(id_oferta) --ultimul pachet
        FROM DELIMITARE
        WHERE id_client = c.id_client
    )
ORDER BY
    c.nume, c.prenume;


--EX 13.

--Actualizarea coloanei "preț" din tabela TRANSPORT pentru transporturile care aparțin pachetelor turistice cu prețul
--mai mare de 1000 de lei.
UPDATE
    TRANSPORT
SET
    pret=2500
WHERE
    id_transport IN (
        SELECT
            id_transport
        FROM
            PACHET_TURISTIC
        WHERE
            pret>1000
        );


--Ștergerea înregistrărilor din tabela CLIENT pentru clientii care au contracte cu anul de terminare mai mic
-- de 2023 .
DELETE FROM CONTRACT
WHERE id_client in (
    SELECT
        id_client
    FROM
        CLIENT
    WHERE id_client IN (
        SELECT
            id_client
        FROM
            CONTRACT
        WHERE
            TO_CHAR(data_terminare, 'YYYY') < '2023'
        )
);
DELETE FROM CLIENT
WHERE id_client IN (
    SELECT
        id_client
    FROM
        CONTRACT
    WHERE
        TO_CHAR(data_terminare, 'YYYY')<'2023'
    );

--Ștergerea înregistrărilor din tabela ANGAJAT pentru angajații care au întocmit mai puțin de doua contracte si
--creșterea salariului cu 500 de lei pentru angajații care au întocmit cel putin 3 contracte.
ALTER TABLE CONTRACT
DROP CONSTRAINT SYS_C008357;
ALTER TABLE CONTRACT
ADD CONSTRAINT CHEIE_ST_CLIENT FOREIGN KEY (id_angajat)
REFERENCES ANGAJAT (id_angajat) ON DELETE CASCADE;
DELETE FROM ANGAJAT
WHERE id_angajat in (
    SELECT
        id_angajat
    FROM
        CONTRACT
    GROUP BY
        id_angajat
    HAVING
        COUNT(id_contract) < 2
    );
UPDATE ANGAJAT
SET
    salariu = salariu + 500
WHERE id_angajat in (
    SELECT
        id_angajat
    FROM
        CONTRACT
    GROUP BY
        id_angajat
    HAVING
        COUNT(id_contract) >= 3);


--EX 14.
--Vizualizarea include numele angajatului, numărul de contracte intocmite, suma totală a plăților
--din aceste contracte.

CREATE VIEW VIZUALIZARE_ANGAJATI AS
SELECT
    a.nume AS Nume_Angajat,
    a.prenume AS Prenume_Angajat,
    COUNT(co.id_contract) AS Numar_Contracte,
    SUM(p.suma_platita) AS Suma_Totala
FROM
    ANGAJAT a
JOIN
    CONTRACT co ON a.id_angajat = co.id_angajat
JOIN
    PLATA p ON co.id_client = p.id_client
GROUP BY
    a.nume, a.prenume;

--DROP VIEW VIZUALIZARE_ANGAJATI;
--Operatie LMD permisa
--Actualizati salariul angajatilor care au suma totala incasats din contrcate mai mare de 2000 de lei
UPDATE ANGAJAT
SET salariu = salariu + salariu * 0.1
WHERE id_angajat IN (
    SELECT
        a.id_angajat
    FROM
        VIZUALIZARE_ANGAJATI v
    JOIN
        ANGAJAT a ON a.nume = v.nume_angajat AND a.prenume = v.prenume_angajat
    WHERE
        suma_totala > 2000
    );

--Operatie LMD nepermisa
--Actualizati coloana Suma_Totala, pentru angajatii care au doua contracte.
UPDATE VIZUALIZARE_ANGAJATI
SET suma_totala = suma_totala * 0.5
WHERE suma_totala = 2;


--EX 15.

--Outer-join
--Afisati date despre clienti, pachete turistice, transport si hotel, incluzand corespondentele dintre aceste tabele.
SELECT
    c.id_client AS id_client,
    c.nume AS Nume_Client,
    c.prenume AS Prenume_Client,
    pt.id_oferta AS id_oferta,
    pt.destinatia AS Destinatie,
    t.tip_vehicul AS Vehicul,
    h.nume AS Nume_Hotel

FROM
    CLIENT c
FULL OUTER JOIN
        DELIMITARE d ON c.id_client = d.id_client
FULL OUTER JOIN
        PACHET_TURISTIC pt ON d.id_oferta = pt.id_oferta
FULL OUTER JOIN
        TRANSPORT t ON pt.id_transport = t.id_transport
FULL OUTER JOIN
        HOTEL h ON pt.id_hotel = h.id_hotel;

--DIVISON
--Afișați toți clienții care au cumpărat toate pachetele turistice disponibile.
--Adaug un client care a cumparat taote pachetele disponibile, pentru a-mi afisa ceva pe ecran
INSERT INTO DELIMITARE (ID_CLIENT, ID_OFERTA)
VALUES (1,1);
INSERT INTO DELIMITARE (ID_CLIENT, ID_OFERTA)
VALUES (1,2);
INSERT INTO DELIMITARE (ID_CLIENT, ID_OFERTA)
VALUES (1,3);
INSERT INTO DELIMITARE (ID_CLIENT, ID_OFERTA)
VALUES (1,4);
INSERT INTO DELIMITARE (ID_CLIENT, ID_OFERTA)
VALUES (1,5);

SELECT
    c.nume ||' '|| c.prenume AS Nume_Client
FROM
    CLIENT c
WHERE NOT EXISTS (
    SELECT
        pt.id_oferta
    FROM
        PACHET_TURISTIC pt
    WHERE NOT EXISTS (
        SELECT
            d.id_oferta
        FROM
            DELIMITARE d
        WHERE d.id_oferta = pt.id_oferta AND d.id_client = c.id_client
    )
);

--ANALIZA TOP-N
--Afisati top 3 pachete turistice, bazate pe pretul transportului.
SELECT *
FROM (
    SELECT
        pt.id_oferta,
        pt.destinatia AS Destinatia,
        t.pret AS Pret_Transport
    FROM
        PACHET_TURISTIC pt
    LEFT JOIN
            TRANSPORT t ON pt.id_transport = t.id_transport
    ORDER BY
        t.pret DESC
)
WHERE ROWNUM <= 3;

--EX 16.
--Să se afișeze numele, prenumele si salariul angajaților care au întocmit un contract cu data de incepere in anul 2024
--si au salariul mai mare de 2000 de lei.
SELECT
    a.nume||' '||a.prenume AS Nume_Angajat,
    a.salariu AS Salariu_Angajat
FROM
    ANGAJAT a
JOIN
    CONTRACT c ON a.id_angajat = c.id_angajat
WHERE
    TO_CHAR(c.data_incepere, 'YYYY') = '2024' AND a.salariu > 2000;

