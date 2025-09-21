use university_db;
-- Part 1 
SELECT title
FROM course
WHERE dept_name = 'Comp. Sci.' AND credits = 3;

-- Part 2
SELECT t.course_id, c.title
FROM takes AS t
JOIN course AS c ON c.course_id = t.course_id
WHERE t.ID = '76543';

-- Part 3 
SELECT dept_name
FROM instructor
GROUP BY dept_name
HAVING COUNT(*) > 2;
