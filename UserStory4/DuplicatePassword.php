<?php
//Turn on error reporting
error_reporting(E_ALL);
//Connect to database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu", "INSERT USERNAME", "INSERT PASSWORD", "INSERT USERNAME");
if($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
?>

<!DOCTYPE html>
	<html lang="en">
		<head>
			<meta charset="UTF-8">
			<title>User Account</title>
			<link rel="stylesheet" type="text/css">
		</head>
		<body>
			<h1 align="center">PASSWORD PLEASE</h1>
			<h2 align="center">Duplicate Password (Testing Only)</h2>
			<h3>User Story: A user should not be able to use a password they have already used.</h3>
			<p><b>Method:</b></p>
			<p>Database 1: all Password Please user accounts</p>
			<p>User 1</p>
			<p>User 2</p>
			<p>User 3</p>
			<p>...</p>
			<p>Database 2: User 1 has the following accounts</p>
			<p>Note: maintain a "database 2" for each user</p>
			<p>Account 1</p>
			<p>Account 2</p>
			<p>Account 3</p>
			<p>...</p>
			<p>Database 3: User 1, Account 1 has the following passwords</p>
			<p>Note: maintain a "database 3" for each individual account that the user enters</p>
			<p>Password 1 (used from Jan - March 2016)</p>
			<p>Password 2 (used from April - July 2016)</p>
			<p>Password 3 (used from August 2016 - Present)</p>
			<p>User 1 now has to update his password for Account 1 to Password 4</p>
			<p>This program checks Password 4 against all previously stored passwords in Database 3</p>
			<div>
				<!--Menu-->
				<form method="post" action="DuplicateCheck.php">
					<fieldset>
						<legend>Enter New Password</legend>
						<p>New Password: <input type="text" name="Password" />
						<input type="Submit" name="Password" value="Password"/></p>
					</fieldset>
				</form>
			</div>			
		</body>
	</html>
