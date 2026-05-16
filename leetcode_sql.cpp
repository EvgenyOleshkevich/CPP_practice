namespace leetcode {

	namespace task_175 {
		/*
		* https://leetcode.com/problems/combine-two-tables/description/
		*/
		/*
		SELECT Person.firstName , Person.lastName, Address.city, Address.state
		FROM Person
		LEFT JOIN Address ON Person.personId=Address.personId;
		*/
	}

	namespace task_176 {
		/*
		* https://leetcode.com/problems/second-highest-salary/description/
		*/
		/*
		SELECT MAX(salary) AS SecondHighestSalary FROM Employee WHERE salary != (SELECT MAX(salary) FROM Employee);
		*/
	}

	namespace task_177 {
		/*
		* https://leetcode.com/problems/nth-highest-salary/description/
		*/
		/*
		CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
		BEGIN
			set N = N - 1;
			RETURN (
				SELECT DISTINCT Salary
				FROM Employee
				ORDER BY Salary DESC
				LIMIT 1 OFFSET N
			);
		END
		*/
	}

	namespace task_178 {
		/*
		* https://leetcode.com/problems/rank-scores/description/
		*/
		/*
		WITH uniq AS (
			SELECT DISTINCT score
			FROM Scores
		)
		SELECT
			uniq.score,
			DENSE_RANK() OVER (ORDER BY score DESC) AS "rank"
		FROM uniq
		JOIN Scores ON Scores.score=uniq.score;


		SELECT
			score,
			DENSE_RANK() OVER (ORDER BY score DESC) AS "rank"
		FROM Scores;


		import pandas as pd

		def order_scores(scores: pd.DataFrame) -> pd.DataFrame:
			scores['rank'] = scores['score'].rank(method = 'dense', ascending = False)
			return scores[['score', 'rank']].sort_values('rank')
		*/
	}

	namespace task_180 {
		/*
		* https://leetcode.com/problems/consecutive-numbers/description/
		*/

		/*
		SELECT DISTINCT num AS ConsecutiveNums
		FROM (
			SELECT
				id,
				num,
				LAG(num, 1) OVER (ORDER BY id) AS prev,
				LAG(num, 2) OVER (ORDER BY id) AS prevPrev
			FROM Logs
		) derived
		WHERE
			num = prev AND
			num = prevPrev;

		Also works

		SELECT DISTINCT
		l1.Num AS ConsecutiveNums
		FROM
			Logs l1,
			Logs l2,
			Logs l3
		WHERE
			l1.Id = l2.Id - 1
			AND l2.Id = l3.Id - 1
			AND l1.Num = l2.Num
			AND l2.Num = l3.Num
		*/

		/*
		import pandas as pd

		def consecutive_numbers(logs: pd.DataFrame) -> pd.DataFrame:

			logs['Prev'] = logs['num'].shift(1)
			logs['PrevPrev'] = logs['num'].shift(2)
			result = logs[
				(logs['num'] == logs['Prev']) &
				(logs['num'] == logs['PrevPrev'])
			][['num']].rename(columns={'num': 'ConsecutiveNums'}).drop_duplicates()

			return result
		*/
	}

	namespace task_181 {
		/*
		* https://leetcode.com/problems/employees-earning-more-than-their-managers/description/
		*/
		/*
		SELECT A.name  AS Employee
		FROM Employee A
		LEFT JOIN Employee B ON A.managerId=B.id
		WHERE A.salary  > B.salary;
		*/
	}

	namespace task_182 {
		/*
		* https://leetcode.com/problems/duplicate-emails/description/
		*/
		/*
		SELECT DISTINCT Person.Email, COUNT(*) FROM Person
		GROUP BY Person.Email
		HAVING
		COUNT(*) > 1;
		*/
	}

	namespace task_183 {
		/*
		* https://leetcode.com/problems/customers-who-never-order/description/
		*/
		/*
		SELECT Customers.name
		FROM Customers
		left join Orders
		on Customers.id = Orders.customerId
		where Orders.customerId Is Null;
		*/
	}

	namespace task_184 {
		/*
		* https://leetcode.com/problems/department-highest-salary/description/
		*/

		/*
		SELECT B.name AS Employee, Department.name AS Department, salary From (
			SELECT e1.id, name, departmentId, salary
			FROM Employee e1
			WHERE salary = (
				SELECT MAX(salary)
				FROM Employee e2
				WHERE e1.departmentId  = e2.departmentId
			)) AS B
		JOIN Department
		WHERE departmentId = Department.id;



		*/


		/* Not solved
		import pandas as pd

		def consecutive_numbers(logs: pd.DataFrame) -> pd.DataFrame:

			logs['Prev'] = logs['num'].shift(1)
			logs['PrevPrev'] = logs['num'].shift(2)
			result = logs[
				(logs['num'] == logs['Prev']) &
				(logs['num'] == logs['PrevPrev'])
			][['num']].rename(columns={'num': 'ConsecutiveNums'}).drop_duplicates()

			return result
		*/
	}

	namespace task_185 {
		/*
		* https://leetcode.com/problems/department-top-three-salaries/description/
		*/

		/*
		SELECT Department.name AS Department, B.name AS Employee, B.salary AS Salary
		From (
			SELECT name, departmentId, salary, 
			DENSE_RANK() OVER (
				PARTITION BY departmentId
				ORDER BY salary DESC
			) AS rnk
			FROM Employee
			) AS B
		JOIN Department
		ON B.departmentId = Department.id
		WHERE B.rnk <= 3;
		*/
	}

	namespace task_197 {
		/*
		* https://leetcode.com/problems/rising-temperature/description/
		*/

		/*
		SELECT id
		FROM (
			SELECT
				id,
				recordDate,
				temperature,
				LAG(temperature, 1) OVER (ORDER BY recordDate) AS prevTemp,
				LAG(recordDate, 1) OVER (ORDER BY recordDate) AS prevDate
			FROM Weather
		) derived
		WHERE
			temperature > prevTemp AND
			recordDate = DATE_ADD(prevDate, INTERVAL 1 DAY);
		*/

		/*
		import pandas as pd

		def rising_temperature(weather: pd.DataFrame) -> pd.DataFrame:
			# Ensure the 'recordDate' column is a datetime type
			weather['recordDate'] = pd.to_datetime(weather['recordDate'])

			# Sorting the DataFrame by 'recordDate' to ensure the shift operation works correctly
			weather.sort_values('recordDate', inplace=True)

			# Creating new columns for the previous day's temperature and record date
			weather['PreviousTemperature'] = weather['temperature'].shift(1)
			weather['PreviousRecordDate'] = weather['recordDate'].shift(1)

			# Filtering the DataFrame to find rows where the temperature is higher
			# than the previous day and the date is exactly one day more than the previous record date
			result = weather[
				(weather['temperature'] > weather['PreviousTemperature']) &
				(weather['recordDate'] == weather['PreviousRecordDate'] + pd.Timedelta(days=1))
			][['id']].rename(columns={'id': 'Id'})

			return result
		*/
	}

	namespace task_511 {
		/*
		* https://leetcode.com/problems/game-play-analysis-i/description/
		*/
		/*
		SELECT player_id, MIN(event_date) AS first_login
		FROM Activity
		GROUP BY player_id;
		*/

		/*
		import pandas as pd

		def game_analysis(activity: pd.DataFrame) -> pd.DataFrame:
			#grouped = activity.groupby('player_id').agg(
			#	first_login= ('event_date', 'min')
			#).reset_index()

			grouped = activity.groupby('player_id', as_index=False).agg(
				first_login= ('event_date', 'min')
			)

			return grouped
		*/
	}

	namespace task_550 {
		/*
		* https://leetcode.com/problems/game-play-analysis-iv/description/
		*/
		/*
		WITH players_with_1 AS (
			SELECT player_id
			FROM (
				SELECT
				player_id,
				event_date,
				event_date - MIN(event_date) OVER (
					PARTITION BY player_id
				) AS days_from_first
				FROM Activity
			)
			WHERE days_from_first = 1
		)
		SELECT ROUND(COUNT(DISTINCT players_with_1.player_id)::numeric
			/ COUNT(DISTINCT Activity.player_id), 2) AS fraction
		FROM Activity
		LEFT JOIN players_with_1
			ON Activity.player_id = players_with_1.player_id;
		*/

		/*
		WITH first_login AS (
			SELECT
				player_id,
				MIN(event_date) AS first_date
			FROM Activity
			GROUP BY player_id
		)
		SELECT
			ROUND(
				COUNT(DISTINCT a.player_id)::numeric / COUNT(DISTINCT f.player_id),
				2
			) AS fraction
		FROM first_login f
		LEFT JOIN Activity a
			ON f.player_id = a.player_id
			AND a.event_date - f.first_date = 1;
		*/

		/*
		import pandas as pd

		def gameplay_analysis(activity: pd.DataFrame) -> pd.DataFrame:
			first_login = activity.groupby('player_id', as_index=False).agg(
				first_login=('event_date', 'min')
			)

			merged = activity.merge(first_login, on="player_id")

			fraction = (
				merged[
					merged["event_date"] - merged["first_login"]
					== pd.Timedelta(days=1)
				]["player_id"]
				.nunique()
				/ activity["player_id"].nunique()
			)

			return pd.DataFrame({
				"fraction": [round(fraction, 2)]
			})
		*/
	}

	namespace task_570 {
		/*
		* https://leetcode.com/problems/managers-with-at-least-5-direct-reports/description/
		*/
		/*
		SELECT name
		FROM Employee
		WHERE id in (
			SELECT managerId
			FROM Employee
			WHERE managerId IS NOT NULL
			GROUP BY managerId
			HAVING COUNT(*) >= 5
		);
		*/

		/*
		SELECT e.name
		FROM Employee e
		JOIN (
			SELECT managerId
			FROM Employee
			WHERE managerId IS NOT NULL
			GROUP BY managerId
			HAVING COUNT(*) >= 5
		) m
			ON e.id = m.managerId;
		*/

		/*
		def find_managers(employee: pd.DataFrame) -> pd.DataFrame:
			managers = employee.groupby('managerId').size()

			manager_ids = managers[managers >= 5].index

			return employee[
				employee['id'].isin(manager_ids)
			][['name']]
		*/
	}

	namespace task_577 {
		/*
		* https://leetcode.com/problems/employee-bonus/description/
		*/
		/*
		SELECT name, bonus
		FROM Employee
		LEFT JOIN Bonus 
			ON Employee.empId = Bonus.empId
		WHERE bonus < 1000 OR bonus IS NULL;
		*/

		/*
		def employee_bonus(employee: pd.DataFrame, bonus: pd.DataFrame) -> pd.DataFrame:
			merged = employee.merge(bonus, on="empId", how='left')
			return merged[(merged['bonus'] < 1000) |
				(merged['bonus'].isna())][['name', 'bonus']]
		*/
	}

	namespace task_584 {
		/*
		* https://leetcode.com/problems/find-customer-referee/description/
		*/
		/*
		SELECT name
		FROM Customer
		WHERE referee_id IS NULL OR referee_id <> 2;
		*/

		/*
		def find_customer_referee(customer: pd.DataFrame) -> pd.DataFrame:
			return customer[(customer['referee_id'] != 2) |
						(customer['referee_id'].isna())][['name']]
		*/
	}

	namespace task_585 {
		/*
		* https://leetcode.com/problems/investments-in-2016/description/
		*/
		/*
		WITH same_tiv_2015 AS (
			SELECT pid 
			FROM (
				SELECT pid,
				MIN(pid) OVER (
					PARTITION BY tiv_2015
				) as min_pid,
				MAX(pid) OVER (
					PARTITION BY tiv_2015
				) as max_pid
				FROM Insurance
			)
			WHERE min_pid <> max_pid
		), unique_lat_lon AS (
			SELECT pid 
			FROM (
				SELECT pid,
				MIN(pid) OVER (
					PARTITION BY lat, lon
				) as min_pid,
				MAX(pid) OVER (
					PARTITION BY lat, lon
				) as max_pid
				FROM Insurance
			)
			WHERE min_pid = max_pid
		)

		SELECT ROUND(CAST(SUM(tiv_2016) AS NUMERIC), 2) AS tiv_2016
		FROM Insurance
				WHERE pid IN(SELECT pid FROM same_tiv_2015) AND pid IN(SELECT pid FROM unique_lat_lon);
		*/


		/*JOIN same_tiv_2015 USING(pid)
		JOIN unique_lat_lon USING(pid)*/

		/*
		WITH checked AS (
			SELECT
				*,
				COUNT(*) OVER (PARTITION BY tiv_2015) AS same_tiv_2015_count,
				COUNT(*) OVER (PARTITION BY lat, lon) AS same_location_count
			FROM Insurance
		)
		SELECT ROUND(CAST(SUM(tiv_2016) AS NUMERIC), 2) AS tiv_2016
		FROM checked
		WHERE same_tiv_2015_count > 1
		  AND same_location_count = 1;
		*/
	}

	namespace task_586 {
		/*
		* https://leetcode.com/problems/customer-placing-the-largest-number-of-orders/description/
		*/
		/*
		SELECT customer_number
		FROM Orders
		GROUP BY customer_number
		ORDER BY  COUNT(*) DESC
		LIMIT 1;
		*/
	}

	namespace task_595 {
		/*
		* https://leetcode.com/problems/big-countries/description/
		*/
		/*
		SELECT name, population, area
		FROM World
		WHERE area >= 3000000  OR population >= 25000000;
		*/
	}

	namespace task_596 {
		/*
		* https://leetcode.com/problems/classes-with-at-least-5-students/description/
		*/
		/*
		SELECT class
		FROM Courses
		GROUP BY class
		HAVING COUNT(*) >= 5;
		*/
	}

	namespace task_602 {
		/*
		* https://leetcode.com/problems/friend-requests-ii-who-has-the-most-friends/description/
		*/
		/*
		WITH requester AS (
					SELECT requester_id AS id, COUNT(*) AS num
					FROM RequestAccepted
					GROUP BY requester_id
				),
		accepter AS (
					SELECT accepter_id AS id, COUNT(*) AS num
					FROM RequestAccepted
					GROUP BY accepter_id
				),
		count_friends As (SELECT COALESCE(a.id, b.id) AS id, COALESCE(a.num, 0) + COALESCE(b.num, 0) AS num
		FROM requester a
		FULL OUTER JOIN accepter b USING(id))

		SELECT *
		FROM count_friends
		WHERE num = (SELECT MAX(num) FROM count_friends);
		*/

		/*
		with base as(select requester_id id from RequestAccepted
		union all
		select accepter_id id from RequestAccepted)


		select id, count(*) num  from base group by 1 order by 2 desc limit 1
		*/
	}

	namespace task_607 {
		/*
		* https://leetcode.com/problems/sales-person/description/
		*/
		/*
		SELECT s.name
		FROM SalesPerson s
		WHERE NOT EXISTS (
			SELECT 1
			FROM Orders o
			JOIN Company c
				ON o.com_id = c.com_id
			WHERE o.sales_id = s.sales_id
			  AND c.name = 'RED'
		);
		*/
	}

	namespace task_608 {
		/*
		* https://leetcode.com/problems/tree-node/description/
		*/
		/*
		SELECT id,
			CASE
				WHEN p_id IS NULL THEN 'Root'
				WHEN id IN (
					SELECT p_id
					FROM tree
					WHERE p_id IS NOT NULL
				) THEN 'Inner'
				ELSE 'Leaf'
			END AS type
		FROM Tree;
		*/
	}

	namespace task_610 {
		/*
		* https://leetcode.com/problems/triangle-judgement/description/
		*/

		/*
		SELECT x, y, z,
		IF(
			x + y > z AND x + z > y AND y + z > x,
			'Yes',
			'No'
		) AS triangle
		FROM Triangle;
		*/

		/*
		SELECT x, y, z,
		CASE
			WHEN 
				x + y > z AND x + z > y AND y + z > x THEN 'Yes'
				ELSE 'No'
			END AS triangle
		FROM Triangle;
		*/
	}

	namespace task_619 {
		/*
		* https://leetcode.com/problems/biggest-single-number/description/
		*/
		/*
		SELECT MAX(num) AS num
		FROM (
				SELECT num
			FROM MyNumbers
			GROUP BY num
			HAVING COUNT(*) = 1);
		*/
	}

	namespace task_626 {
		/*
		* https://leetcode.com/problems/exchange-seats/description/
		*/
		/*
		SELECT
			CASE
				WHEN id % 2 = 1 AND id = (SELECT MAX(id) FROM Seat) THEN id
				WHEN id % 2 = 1 THEN id + 1
				ELSE id - 1
			END AS id,
			student
		FROM Seat
		ORDER BY id;
		*/

		/*
		WITH prev_next AS (
			SELECT
				id,
				student,
				LAG(student) OVER (ORDER BY id) AS prev_student,
				LEAD(student) OVER (ORDER BY id) AS next_student
			FROM Seat
		)
		SELECT
			id,
			CASE
				WHEN id % 2 = 1 AND next_student IS NOT NULL THEN next_student
				WHEN id % 2 = 0 THEN prev_student
				ELSE student
			END AS student
		FROM prev_next
		ORDER BY id;
		*/
	}

	namespace task_627 {
		/*
		* https://leetcode.com/problems/swap-sex-of-employees/description/
		*/
		/*
		UPDATE Salary
		SET
			sex = CASE
				WHEN sex = 'f' THEN 'm'
				ELSE 'f'
			END;
		*/
	}

	namespace task_1045 {
		/*
		* https://leetcode.com/problems/customers-who-bought-all-products/description/
		*/
		/*
		SELECT customer_id
		FROM Customer
		GROUP BY customer_id
		HAVING COUNT(DISTINCT product_key) = (
			SELECT COUNT(*)
			FROM Product);
		*/
	}

	namespace task_1050 {
		/*
		* https://leetcode.com/problems/actors-and-directors-who-cooperated-at-least-three-times/description/
		*/
		/*
		SELECT actor_id, director_id
		FROM ActorDirector
		GROUP BY actor_id, director_id
		HAVING COUNT(*) >= 3;
		*/
	}

	namespace task_1068 {
		/*
		* https://leetcode.com/problems/product-sales-analysis-i/description/
		*/
		/*
		SELECT product_name, year, price
		FROM Sales
		JOIN Product
			USING(product_id);
		*/
	}

	namespace task_1070 {
		/*
		* https://leetcode.com/problems/product-sales-analysis-iii/description/
		*/
		/*
		WITH first_year AS (
			SELECT product_id, MIN(year) AS first_year
			FROM Sales
			GROUP BY product_id
		)

		SELECT Sales.product_id, first_year, quantity, price
		FROM Sales
		JOIN first_year
			ON (Sales.product_id, Sales.year) = (first_year.product_id, first_year.first_year);
		*/
	}

	namespace task_1075 {
		/*
		* https://leetcode.com/problems/product-sales-analysis-iii/description/
		*/
		/*
		SELECT project_id, ROUND(AVG(experience_years), 2) AS average_years
		FROM Project
		JOIN Employee USING(employee_id)
		GROUP BY project_id;
		*/
	}
}