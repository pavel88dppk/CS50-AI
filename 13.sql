SELECT DISTINCT(name)
FROM (SELECT * FROM people 
JOIN (SELECT * FROM stars 
JOIN movies ON movies.id = movie_id) ON people.id = person_id)
WHERE title IN(SELECT title FROM people 
JOIN (SELECT * FROM stars JOIN movies ON id = movie_id) 
ON person_id = people.id 
WHERE name = "Kevin Bacon" AND birth = 1958);


SELECT DISTINCT(name) FROM people 
WHERE name != "Kevin Bacon" AND id IN (SELECT person_id FROM stars Where movie_id IN
(SELECT movie_id FROM stars Where person_id IN
(SELECT id FROM people WHERE name IS 'Kevin Bacon' and birth = 1958)));
