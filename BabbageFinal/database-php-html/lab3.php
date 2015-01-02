<!DOCTYPE html>
<html>
	<head>
		<meta charset=UTF-8>
		<title>CS 3380 Lab 3</title>
	</head>
	<body>
		<form method="POST" action="/~jmcgdd/cs3380/lab3/lab3.php">
			Search for a: <input type="radio" name="selection" value="Country">Country</input>
			<input type="radio" name="selection" value="City">City</input>
			<input type="radio" name="selection" value="Language">Language</input>
			<br /><br />
			That begins with: <input type="text" name="search"/>
			<br /><br />
			<input type="submit" name="submit" value="Submit" />
		</form>
		<br />
		<hr />
		<br />
	</body>
</html>

<?php
	/***************************\
	!	John Curley-16013276	!
	!	Lab: 9:00AM Tues. 		!
	!	TA: John Benjamin		!
	!	Assignment: Lab3		!
	!	Due: 9/11/2013			!
	\***************************/
	
	//Function to print the table corresponding to query input
	function print_table($result){
		// Printing results in HTML
		//build a table as in lab 1
		echo "<table border='1'>\n";


		#build header row using pg_field name iterated over pg_num_fields
		$i = pg_num_fields($result);
		echo "<p>\n\nThere were <em>" . pg_num_rows($result) . "</em> rows returned.\n\n</p>";

		//pg_field_name
		echo "<tr>";
		for($j=0;$j<$i;$j++) {
			echo "<th><strong>";
			$field_name = pg_field_name($result,$j);
			echo(htmlspecialchars($field_name));
			echo "</strong></th>";
		}
		echo "</tr>";
		while ($line = pg_fetch_array($result, null, PGSQL_ASSOC)) {
			echo "\t<tr>\n";
			//the $line variable returned from PG_FETCH_ARRAY is an
			//associative array with each tuple stored as a key => value pair
			foreach ($line as $col_value) {
				echo "\t\t<td>$col_value</td>\n";
			}
			echo "\t</tr>\n";

		}
		echo "</table>\n";
	}
	//After Submit button is pressed
	if(isset($_POST['submit'])){
		//Connects to server
		$conn = pg_connect("host=dbhost-pgsql.cs.missouri.edu dbname=jmcgdd user=jmcgdd password=dSC5qfNy")
			or die("Could not connect: " . pg_last_error());
		//Sanitizes user input
		$mysearch = htmlspecialchars($_POST['search']);
		//Represents which radio button was selected
		$selection = $_POST['selection'];
		//If countries are to be queried
		if($selection=="Country"){
			$query = "SELECT * FROM lab2.country WHERE name ILIKE $1||'%' ORDER BY name ASC";
			$stmt = pg_prepare($conn, $selection, $query);
		}
		//If cities are to be queried
		else if($selection=="City"){
			$query = "SELECT * FROM lab2.city WHERE name ILIKE $1||'%' ORDER BY name ASC";
			$stmt = pg_prepare($conn, $selection, $query);
		}
		//If languages are to be queried
		else{
			$query = "SELECT * FROM lab2.country_language WHERE language ILIKE $1||'%' ORDER BY language ASC";
			$stmt = pg_prepare($conn, $selection, $query);
		}
		//Connects to corresponding prepare statement based on $selection
		$result = pg_execute($conn, $selection, array($mysearch));
		//If result failed, print the latest error message
		if(!$result){
			die("Unable to execute: " . pg_last_error($conn));
		} 
		//If result is valid, print the table based on the query
		else{
			//results are good so output them to HTML
			print_table($result);
		}
	}
?>