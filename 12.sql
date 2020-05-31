SELECT title FROM movies
JOIN (SELECT * FROM people JOIN stars ON person_id = people.id) ON movie_id = movies.id
WHERE name = "Johnny Depp" AND movies.title IN(SELECT title FROM movies
JOIN (SELECT * FROM people JOIN stars ON person_id = people.id)ON movie_id = movies.id
WHERE name = "Helena Bonham Carter");