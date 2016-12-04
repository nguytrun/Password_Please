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
			<title>Account Information</title>
			<link rel="stylesheet" type="text/css">
		</head>
		<body>
			<h1 align="center">PASSWORD PLEASE</h1>
			<h2 align="center">Account Information</h2>
			<div>
				<br>
				<table>
					<thead>
						<tr>
							<th>Account Name</th>
							<th>Username</th>
							<th>Password</th>
						</tr>
					</thead>
					<?php
					if(!($stmt = $mysqli->prepare("SELECT Account, Username, Password FROM UserAccount WHERE AccountID = ?"))){
						echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
					}
					
					if(!($stmt->bind_param("i",$_POST['Account']))){
						echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
					}
					
					if(!$stmt->execute()){
						echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
					}
					
					if(!$stmt->bind_result($Account, $Username, $Password)){
						echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
					}
					
					while($stmt->fetch()){
					 echo "<tr>\n<td>\n" . $Account . "\n</td>\n<td>\n" . $Username . "\n</td>\n<td>\n" . $Password . "\n</td>\n</tr>";
					}
					$stmt->close();
					?>
				</table>
			</div>
		</body>
	</html>
