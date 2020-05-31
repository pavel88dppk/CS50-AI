SELECT title FROM people
JOIN (SELECT * FROM stars JOIN (SELECT * FROM movies JOIN ratings ON ratings.movie_id = id)ON id = stars.movie_id)
ON people.id = person_id
WHERE name = "Chadwick Boseman"
ORDER BY rating DESC
LIMIT 5;