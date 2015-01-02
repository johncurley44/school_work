<!DOCTYPE html>
<html>
	<head>
		<meta charset=UTF-8>
		<title>CS 3380 Lab 2</title>
	</head>
	<body>
		<form method="POST" action="/~jmcgdd/cs3380/lab2/lab2.php">
			<select name="query">
				<option value="1" >Query 1</option>
				<option value="2" >Query 2</option>
				<option value="3" >Query 3</option>
				<option value="4" >Query 4</option>
				<option value="5" >Query 5</option>
				<option value="6" >Query 6</option>
				<option value="7" >Query 7</option>
				<option value="8" >Query 8</option>
				<option value="9" >Query 9</option>
				<option value="10" >Query 10</option>
				<option value="11" >Query 11</option>
				<option value="12" >Query 12</option>
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
	!	Assignment: Lab2		!
	!	Due: 9/4/2013			!
	\***************************/
	
	//Function to print the table corresponding to query input
	function print_table($qstatement){
		// Passes query, if fails, prints error statement
		$result = pg_query($qstatement) or die("Query failed: " . pg_last_error());
		// Number of columns in table
		$numfields = pg_num_fields($result);
		// Prints the number of rows in table
		echo "<p>\n\nThere were <em>" . pg_num_rows($result) . "</em> rows returned.\n\n</p>";
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
		// Cleans user input
		$s = htmlspecialchars($_POST['query']);
		// Switch statement based on drop down selection for query
		switch($s) {
			// 1.) 	List all countries that have a surface area greater than 1000000; the query should also return each
			//		country's region, head of state, and form of government. The countries should be ordered by surface
			//		area from largest to smallest.
			case 1:
				$query = "SELECT name, region, head_of_state, government_form FROM lab2.country WHERE surface_area > 1000000 ORDER BY surface_area DESC";
				print_table($query);
				break;
			// 2.) List the country name, language and percentage of speakers for all languages where the percentage of
			//		speakers is greater than 90% and the language is an official language. The results should be listed in
			//		decreasing order of percentage
			case 2:
				$query = "SELECT name, language, percentage FROM lab2.country AS c INNER JOIN lab2.country_language AS cl USING (country_code) WHERE (cl.percentage >90) AND (cl.is_official = TRUE) ORDER BY cl.percentage DESC";
				print_table($query);
				break;
			// 3.) List all of the distinct languages that are spoken by more than 50% of speakers in some country but is
			//		not an official language in that country. Present the results in alphabetical order of language from A
			//		to Z.
			case 3:
				$query = "SELECT DISTINCT language FROM lab2.country_language WHERE (percentage > 50) AND (is_official = FALSE) ORDER BY language ASC";
				print_table($query);
				break;
			// 4.) List each country and all the cities in that country. Include the population of each city in your results.
			//		The records should ordered by country name from A to Z, then by decreasing population and finally
			//		by city name from A to Z.
			case 4: 
				$query = "SELECT c.name, c.population, co.name AS coname FROM lab2.city AS c INNER JOIN lab2.country AS co USING (country_code) ORDER BY coname ASC, population DESC, name ASC";
				print_table($query);
				break;
			// 5.) List all official languages with the number of speakers (not the percentage) of that language. For each
			//		record in the table, also display the country name and capital. Your results should be first ordered by
			//		country name (from A to Z) and then by the number of speakers (from smallest to largest). (236 237
			//		results)
			case 5:
				$query = "SELECT co.name AS country, c.name AS capital, cl.language, ROUND((cl.percentage * co.population)/100) AS speakers FROM lab2.city AS c INNER JOIN (lab2.country AS co INNER JOIN lab2.country_language AS cl USING (country_code)) ON (co.capital=c.id) WHERE cl.is_official = TRUE ORDER BY country ASC, speakers ASC";
				print_table($query);
				break;
			// 6.) List all cities with their district and population that have more than 4500000 residents. Results should
			// 		be ordered by city name from A to Z.
			case 6:
				$query = "SELECT name AS city, district, population FROM lab2.city WHERE population > 4500000 ORDER BY city ASC";
				print_table($query);
				break;
			// 7.) List all cities and their district and country name if the city name begins with the letters 'M' and ends
			// 		with 'd'. Results should be ordered by increase country name (A to Z) and then from increasing city
			//		name.
			case 7:
				$query = "SELECT c.name AS city, district, co.name AS country FROM lab2.city AS c INNER JOIN lab2.country AS co USING (country_code) WHERE (SUBSTRING(c.name from 1 for 1) = 'M') AND (SUBSTRING(c.name from LENGTH(c.name) for 1)='d') ORDER BY country ASC, city ASC";
				print_table($query);
				break;
			// 8.) List all countries that have a population greater than 25,000,000 and have an unofficial language spoken
			//		by more than 3 percent of the population. Results should alphabetize the country names. Hint: use
			//		DISTINCT.
			case 8:
				$query = "SELECT DISTINCT name FROM lab2.country AS co INNER JOIN lab2.country_language AS cl USING (country_code) WHERE (population >25000000) AND (is_official = FALSE) AND (percentage > 3) ORDER BY name ASC";
				print_table($query);
				break;
			// 9.) List the sixth through twentieth oldest countries with the year of their independence, population,
			//		surface area, GNP and form of government. The results should be ordered by year of independence
			//		from oldest to newest.
			case 9:
				$query = "SELECT name, indep_year, population, surface_area, gnp, government_form FROM lab2.country ORDER BY indep_year ASC LIMIT 15 OFFSET 5";
				print_table($query);
				break;
			// 10.) List the twenty countries with the lowest life expectancy. Include each country's name, continent, year
			//		of independence form of government and life expectancy in the results.
			case 10:
				$query = "SELECT name, continent, indep_year, government_form, life_expectancy FROM lab2.country ORDER BY life_expectancy ASC LIMIT 20";
				print_table($query);
				break;
			// 11.) List the countries that that had a decrease in GNP. (That is, gnp old is larger than gnp.) Show the
			//		country name, form of government, GNP, old GNP and the difference between the two GNP values.
			//		The results should be ordered by the difference between the two GNP numbers from largest difference
			//		to smallest difference.
			case 11:
				$query  = "SELECT name, government_form, gnp, gnp_old, (gnp - gnp_old) AS delta FROM lab2.country WHERE gnp < gnp_old ORDER BY delta ASC";
				print_table($query);
				break;
			// 12.) List all countries with their per capita GNP (i.e. it's GNP divided by it's population), continent and
			//		year of independence. Results should be ordered from largest per capita GNP to smallest. (For obvious
			//		reasons, you'll need to exclude records where the population is listed as 0).
			case 12:
				$query = "SELECT name, (gnp/population) AS per_capita_gnp, continent, indep_year FROM lab2.country WHERE (population > 0) ORDER BY per_capita_gnp DESC";
				print_table($query);
				break;
			default:
				
				break;
		}
		
		pg_free_result($result);

		pg_close($dbconn);
	}
?>