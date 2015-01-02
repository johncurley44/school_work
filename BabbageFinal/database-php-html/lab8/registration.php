<!DOCTYPE html>
<html>
	<head>
		<meta charset=UTF-8>
		<title>CS 3380 Lab 8</title>
	</head>
	<body>
		<form method="POST" action="/~jmcgdd/cs3380/lab8/registration.php">
			<table border="1">
			<tr><td>Desired User Name:</td><td><input type="text" name="user" /></td></tr>
			<tr><td>Desired Password:</td><td><input type="text" name="pass" /></td></tr></table>
			<br />
			<input type="submit" name="submit" value="Submit" />
			<br />
		</form>
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
	if(isset($_POST['submit'])){
		//Connects to server 
		$conn = pg_connect("host=dbhost-pgsql.cs.missouri.edu dbname=jmcgdd user=jmcgdd password=dSC5qfNy")
			or die("Could not connect: " . pg_last_error());
		$req_user = htmlspecialchars($_POST['user']);
		$req_pass = htmlspecialchars($_POST['pass']);
		//Checks if username exists already, if it does, prints message, allows user to re-enter information
		$query = 'SELECT username FROM lab8.user_info WHERE username = $1';
		pg_prepare($conn, "exists", $query);
		$result = pg_execute($conn, "exists", array($req_user));
		$num_rows_result = pg_num_rows($result); 
		if($num_rows_result > 0){
			echo "Username is already taken, please try a different username.";
		}
		//If username doesnt exist, insert user info to tables
		else{
			//Insert the new username into user_info table
			$new_user_q = 'INSERT INTO lab8.user_info VALUES ($1, DEFAULT, NULL)';
			pg_prepare($conn, "new_user", $new_user_q);
			$new_user_result = pg_execute($conn, "new_user", array($req_user));
			//create salt and hashed password using salt
			$salt = sha1(rand());
			$prehash_string = $req_pass.$salt;
			$hashed_pass = sha1($prehash_string);
			//insert user info, including hashed pass, into authentication table
			$new_auth_q = 'INSERT INTO lab8.authentication VALUES ($1, $2, $3)';
			pg_prepare($conn, "new_auth", $new_auth_q);
			$new_auth_result = pg_execute($conn, "new_auth", array($req_user, $hashed_pass, $salt));
			//start session and save user info after login, send to home page
			session_start();
			$_SESSION['user'] = $req_user;
			$_SESSION['pass'] = $pass_id;
			//Add login info to log
			$log_query = "INSERT INTO lab8.log VALUES (DEFAULT, $1, '192.168.1.102', DEFAULT, 'user created')";
			pg_prepare($conn, "log", $log_query);
			$log_result = pg_execute($conn, "log", array($req_user));
			
			header('Location: /~jmcgdd/cs3380/lab8/home.php');
		}
	}		
	
?>
