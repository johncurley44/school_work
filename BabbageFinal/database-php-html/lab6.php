<!DOCTYPE html>
<html>
	<head>
		<meta charset=UTF-8>
		<title>CS 3380 Lab 6</title>
	</head>
	<body>
		<form method="POST" action="/~jmcgdd/cs3380/lab6/lab6.php">
			<select name="query">
				<option value="1" >Query 1</option>
				<option value="2" >Query 2</option>
				<option value="3" >Query 3</option>
				<option value="4" >Query 4</option>
				<option value="5" >Query 5</option>
				<option value="6" >Query 6</option>
				<option value="7" >Query 7</option>
				<option value="8" >Query 8</option>
			</select>
			<input type="submit" name="submit" value="Execute" />
		</form>
		<br />
		<hr />
		<br />
		<?php
			ob_start();
		?>
		<strong>Select a query from the above list</strong>
	</body>
</html>

<?php
	/***************************\
	!	John Curley-16013276	!
	!	Lab: 9:00AM Tues. 		!
	!	TA: John Benjamin		!
	!	Assignment: Lab6		!
	!	Due: 10/4/2013			!
	\***************************/
	
	//Function to print the table corresponding to query input
	function print_table($qstatement){
		// Passes query, if fails, prints error statement
		$result = pg_query($qstatement) or die("Query failed: " . pg_last_error());
		// Number of columns in table
		$numfields = pg_num_fields($result);
		// Prints the number of rows in table
		echo "<p>There were <em>" . pg_num_rows($result) . "</em> rows returned.\n\n</p>";
		echo "<table border = '1'>";
		// Prints the name of each field at top of table in bold
		for($i=0; $i < $numfields; $i++){
			$coltitle = pg_field_name($result, $i);
			echo "<th>$coltitle</th>";
		}
		// Prints the data for each row
		while ($line = pg_fetch_array($result, null, PGSQL_ASSOC)) {
			echo "\t<tr>\n";
			foreach ($line as $col_value) {
				echo "\t\t<td>$col_value</td>\n";
			}
			echo "\t</tr>\n";
		}
		echo "</table>\n";
	}
	
	// If statement for when "Execute" button is pressed
	if(isset($_POST['submit'])){
		$dbconn = pg_connect("host=dbhost-pgsql.cs.missouri.edu dbname=jmcgdd user=jmcgdd password=dSC5qfNy")
			or die("Could not connect: " . pg_last_error());
		ob_end_clean();
		$s = htmlspecialchars($_POST['query']);
		// Switch statement based on drop down selection for query
		switch($s) {
			//List the average, minimum, and maximum population of all countries with a non-zero population in
			//	the database
			case 1:
				$query = "SELECT AVG(population), MIN(population), MAX(population) FROM lab6.country WHERE population > 0";
				print_table($query);
				break;
			//List the total population, surface area and GNP by continent; order the results from smallest to largest
			//	surface area.
			case 2:
				$query = "SELECT continent, SUM(population) AS total_pop, SUM(surface_area) AS total_area, SUM(gnp) AS total_gnp FROM lab6.country GROUP BY(country.continent) ORDER BY total_area";
				print_table($query);
				break;
			//Generate a list of all forms of government with the count of how many countries have that form of
			//	government. Also, list the most recent year in which any country became independent with that form of
			//	government. The results should be ordered by the independence year field in decreasing order. (Note:
			//	Some countries may have NULL for the independence year. Those countries should not be considered
			//	when finding the earliest independence year.)
			case 3:
				$query = "SELECT government_form, COUNT(*), MAX(indep_year) AS most_recent_indep_year FROM lab6.country WHERE indep_year IS NOT NULL GROUP BY(country.government_form) ORDER BY most_recent_indep_year ASC";
				print_table($query);
				break;
			//For each country that contains a city, list the total number of cities it contains. Order the results in
			//	descending order of the number of cities
			case 4:
				$query = "SELECT co.name, COUNT(c.name) FROM lab6.country AS co INNER JOIN lab6.city AS c USING (country_code) GROUP BY (co.name) ORDER BY COUNT(c.name) DESC";
				print_table($query);
				break;
			//List the country name, it's population, and the sum of the populations of all cities in that country.
			//	Add a fourth field to your query that calculates the percent of urban population for each country. (For
			//	the purposes of this example, assume that the sum of the populations of all cities listed for a country
			//	represent that country's entire urban population.) Order the results of this query in decreasing order
			//	of urban population percentage.
			case 5:
				$query = "	SELECT co.name, co.population AS country_population, urban_population, urban_pct
							FROM lab6.country AS co, 
							(
								SELECT country_code, SUM(c.population) AS urban_population, ((SUM(c.population::double precision)/(co.population::double precision))*100) AS urban_pct 
								FROM lab6.country AS co INNER JOIN lab6.city AS c USING(country_code) 
								GROUP BY country_code
							) AS sub
							WHERE co.country_code = sub.country_code
							ORDER BY urban_pct DESC";
				print_table($query);
				break;
			//For each country, list the largest population of any of its cities and the name of that city. Order the
			//	results alphabetically by country.
			case 6:
				$query = "	SELECT co.name, c.name AS largest_city, max_pop AS population
							FROM lab6.country AS co INNER JOIN lab6.city AS c USING (country_code),
							(
								SELECT country_code, MAX(population) AS max_pop 
								FROM lab6.city 
								GROUP BY country_code
							) AS sub
							WHERE c.country_code = sub.country_code 
							AND c.population = max_pop
							ORDER BY co.name ASC";
				print_table($query);
				break;
			//List the countries in ascending order beginning with the country with the smallest number of cities in
			//	the database and ending with the country with the largest number of cities in the database. Cities
			//	that have the same number of cities should be sorted alphabetically from A to Z.
			case 7:
				$query = "SELECT co.name, count
						  FROM lab6.country AS co,
							(
							SELECT country_code, COUNT(id) AS count
							FROM lab6.city
							GROUP BY country_code ORDER BY count
							) AS sub
						  WHERE co.country_code = sub.country_code
						  ORDER BY count, co.name";
				print_table($query);
				break;
			//For each country with 5-10 languages, list the number of languages spoken, in descending order by
			//	number of languages as well as the name of the capital for that country
			case 8:
				$query = "
						SELECT co.name, c.name AS capital, lang_count
						FROM lab6.country AS co INNER JOIN lab6.city AS c USING (country_code),
						(
							SELECT country_code, COUNT(language) AS lang_count
							FROM lab6.country_language
							GROUP BY country_code
						) AS sub
						WHERE co.country_code = sub.country_code
						AND c.id = co.capital
						AND lang_count >= 5
						AND lang_count <= 10
						ORDER BY lang_count DESC, capital DESC";
				print_table($query);
				break;
			default:
				break;
		}
	}
	pg_free_result($result);
	pg_close($dbconn);
?>	