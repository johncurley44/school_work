<!DOCTYPE html>
<html>
	<head>
		<meta charset=UTF-8>
		<title>CS 3380 Lab 8</title>
	</head>
	<body>
		<form method="POST" action="/~jmcgdd/cs3380/lab8/index.php">
			<table border="1">
			<tr><td>User Name:</td><td><input type="text" name="user" /></td></tr>
			<tr><td>Password:</td><td><input type="text" name="pass" /></td></tr></table>
			<br />
			<input type="submit" name="login" value="Log In" />
			<br />
			<a name="register" href="/~jmcgdd/cs3380/lab8/registration.php"> New User? Click Here to Register. </a>
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
	if(isset($_POST['login'])){
		//Connects to server
		$conn = pg_connect("host=dbhost-pgsql.cs.missouri.edu dbname=jmcgdd user=jmcgdd password=dSC5qfNy")
			or die("Could not connect: " . pg_last_error());
		//sanitize user input
		$user_id = htmlspecialchars($_POST['user']);
		$pass_id = htmlspecialchars($_POST['pass']);
		//check to see if user id input exists in table
		$check_user_q = 'SELECT username FROM lab8.user_info WHERE username = $1';
		pg_prepare($conn, "check_user", $check_user_q);
		$check_user_result = pg_execute($conn, "check_user", array($user_id));
		$num_results_user = pg_num_rows($check_user_result); 
		//if the username is found
		if($num_results_user > 0){
			//find salt associated with query
			$salt_query = 'SELECT salt FROM lab8.authentication WHERE username = $1';
			pg_prepare($conn, "get_salt", $salt_query);
			$salt_result = pg_execute($conn, "get_salt", array($user_id));
			$num_results_salt = pg_num_rows($salt_result);
			//if the salt is found
			if($num_results_salt > 0){
				$salt_array = pg_fetch_array($salt_result, null, PGSQL_NUM);
				$salt_string = $salt_array[0];
				//concat the salt to the end of the user pass
				$salted_pass = sha1($pass_id.$salt_string);
				//look for username and hashed password combo in authentication table that matches entered username and hashed password input
				$pass_query = 'SELECT username FROM lab8.authentication WHERE username = $1 AND password_hash = $2';
				pg_prepare($conn, "get_pass_hash", $pass_query);
				$pass_result = pg_execute($conn, "get_pass_hash", array($user_id, $salted_pass));
				$num_results_pass = pg_num_rows($pass_result);
				if($num_results_pass > 0){
					session_start();
					$_SESSION['user']=$user_id;
					$_SESSION['pass']=$pass_id;
					//Add login info to log
					$log_query = "INSERT INTO lab8.log VALUES (DEFAULT, $1, '192.168.1.102', DEFAULT, 'login')";
					pg_prepare($conn, "log", $log_query);
					$log_result = pg_execute($conn, "log", array($user_id));
					
					header('Location: /~jmcgdd/cs3380/lab8/home.php');
				}
				else{
					echo "Incorrect Password";
				}

			}
			else{
				echo "Could not find salt, error";
			}
		}
		else{
			echo "Incorrect User Name";
		}
	} 
	if(session_id()){
		header('Location: /~jmcgdd/cs3380/lab8/home.php');
	}
	
	
	
?>