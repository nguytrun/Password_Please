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
			<link rel="stylesheet" href="Final Project.css" type="text/css">
		</head>
		<body>
			<h1 align="center">PASSWORD PLEASE</h1>
			<h2 align="center">User Accounts</h2>
			<div>
				<!--Menu-->
				<form method="post" action="AccountDisplay.php">
					<fieldset>
						<legend>My User Accounts</legend>
							<p>Select User Account: <select name="Account">
								<?php
									if(!($stmt = $mysqli->prepare("SELECT AccountID, Account FROM UserAccount"))){
									echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
									}
									if(!$stmt->execute()){
										echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
									}
									if(!$stmt->bind_result($AccountID, $Account)){
										echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
									}
									while($stmt->fetch()){
									 echo '<option value=" '. $AccountID . ' "> ' . $Account . '</option>\n';
									}
									$stmt->close();
								?>
							</select></p>
						<input type="Submit" name="selectAccount" value="Select"/>
					</fieldset>
				</form>
				<!--Testing
				<h2 align="center">This section is for testing only</h2>
				<form method="post" action="DropDownMenuTesting.php">
					<fieldset>
						<legend>For Testing Only</legend>
						<p><b>This page verifies that a new account is added, so that the drop down menu reflects the change</b></p>
						<p>Account Name: <input type="text" name="AccountName" /> Username: <input type="text" name="UserName" /> Password: <input type="text" name="Password" /></p>
						<input type="Submit" name="accountAdd" value="Add Account"/>
					</fieldset>
				</form>
				<form method="post" action="DropDownMenuTesting.php">
					<fieldset>
						<legend>For Testing Only</legend>
						<p><b>This page verifies that an existing account is deleted, so that the drop down menu reflects the change</b></p>
						<p>Delete User Account: <select name="Account">
								<?php
									if(!($stmt = $mysqli->prepare("SELECT AccountID, Account FROM UserAccount"))){
									echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
									}
									if(!$stmt->execute()){
										echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
									}
									if(!$stmt->bind_result($AccountID, $Account)){
										echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
									}
									while($stmt->fetch()){
									 echo '<option value=" '. $AccountID . ' "> ' . $Account . '</option>\n';
									}
									$stmt->close();
								?>
						</select></p>
						<input type="Submit" name="deleteAccount" value="Delete"/>
					</fieldset>
				</form>-->
			</div>			
		</body>
	</html>
