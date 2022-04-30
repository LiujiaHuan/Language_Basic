------------------------------------------------------------------group_concat
SELECT 
    GROUP_CONCAT(country)
FROM
    customers;
------------------------------------------------------------------ ~ + distinct
SELECT 
    GROUP_CONCAT(DISTINCT country)
FROM
    customers;
------------------------------------------------------------------- ~ + order by
SELECT 
    GROUP_CONCAT(DISTINCT country
        ORDER BY country)
FROM
    customers;
------------------------------------------------------------------- ~ + separator
SELECT 
    GROUP_CONCAT(DISTINCT country
        ORDER BY country
        SEPARATOR ';')
FROM
    customers;
