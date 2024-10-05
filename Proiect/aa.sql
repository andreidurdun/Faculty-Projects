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

delete from CLIENT
WHERE ID_CLIENT=21;
select * from CLIENT;
SELECT * FROM PLATA;


SELECT
    c.nume, COUNT(pt.id_oferta)
FROM
    CLIENT c;
join  DELIMITARE d ON c.id_client=d.id_client
join PACHET_TURISTIC pt ON d.id_oferta=pt.id_oferta
group by c.nume
