<!DOCTYPE html>
<html>
	<head>
		<meta charset=UTF-8>
		<title>CS 3380 Lab 8</title>
	</head>
	<body>
		<form method="POST" action="/~jmcgdd/cs3380/lab8/lab8.php">
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