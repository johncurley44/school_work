<!DOCTYPE html>
<html>
	<head>
		<meta charset=UTF-8>
		<title>CS 3380 Lab 8</title>
	</head>
	<body>
		<form method="POST" action="/~jmcgdd/cs3380/lab8/logout.php">
			<input type="submit" name="logout" value="Log Out" />
		</form>
		<form method="POST" action="/~jmcgdd/cs3380/lab8/update.php">
			<input type="submit" name="update" value="Update" />
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
	!	Assignment: Lab8		!
	!	Due: 10/20/2013			!
	\***************************/
	if(!isset($_SERVER['HTTPS'])){
		$redir = "https://".$_SERVER['HTTP_HOST'].$_SERVER['REQUEST_URI'];
		header("Location: $redir");
	}
	session_start();
	if(isset($_SESSION['user'])){
		//Connects to server
		$conn = pg_connect("host=dbhost-pgsql.cs.missouri.edu dbname=jmcgdd user=jmcgdd password=dSC5qfNy")
			or die("Could not connect: " . pg_last_error());
		//Display current user information
		$disp_username = $_SESSION['user'];
		$disp_query = 'SELECT * FROM lab8.user_info WHERE username = $1';
		pg_prepare($conn, "disp_info", $disp_query);
		$disp_result = pg_execute($conn, "disp_info", array($disp_username));
		$line = pg_fetch_array($disp_result, null, PGSQL_NUM);
		$numfields = pg_num_fields($disp_result);
		echo "<table border='1'>";
		for($i=0; $i < $numfields; $i++){
			$coltitle = pg_field_name($disp_result, $i);
			echo "<th>$coltitle</th>";
		}
		echo "<tr>";
		foreach($line as $valrow){
			echo "<td>$valrow</td>\n";
		}
		echo "</tr></table>";
		echo "<br/><br/>";
		//Display current user log in history
		$hist_query = 'SELECT log_date, ip_address FROM lab8.log WHERE username = $1 ORDER BY log_id ASC';
		pg_prepare($conn, "hist_info", $hist_query);
		$hist_result = pg_execute($conn, "hist_info", array($disp_username));
		$numfields2 = pg_num_fields($hist_result);
		echo "<table border='1'><tr>";
		
		for($i=0; $i < $numfields2; $i++){
			$coltitle = pg_field_name($hist_result, $i);
			echo "<th>$coltitle</th>";
		}
		while ($line2 = pg_fetch_array($hist_result, null, PGSQL_ASSOC)) {
			echo "\t<tr>\n";
			foreach($line2 as $valrow2){
				echo "<td>$valrow2</td>\n";
			}
			echo "</tr>";
		}
		echo "</table>";
	}
	else{
		header('Location: /~jmcgdd/cs3380/lab8/index.php');
	}
	
?>
