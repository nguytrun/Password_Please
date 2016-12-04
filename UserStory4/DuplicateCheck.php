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
			<title>DuplicateCheck</title>
			<link rel="stylesheet" type="text/css">
		</head>
		<body>
			<h1 align="center">PASSWORD PLEASE</h1>
			<h2 align="center">Duplicate Password (Testing Results)</h2>
			<?php
			if(!($stmt = $mysqli->prepare("INSERT INTO Passwords (Password) VALUES (?)"))){
				echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
			}
			if(!($stmt->bind_param("s",$_POST['Password']))){
				echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
			}
			if(!$stmt->execute()){
				echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
			} else {
				echo "Added password.";
			}
			?>
			<div>
				<br>
				<p><b>Current Passwords</b></p>
				<p>Note that this testing feature does not actually add new passwords into database, as that is not part of the user story</p>
				<table>
					<thead>
						<tr>
							<th>PasswordID</th>
							<th>Password</th>
						</tr>
					</thead>
					<?php
					if(!($stmt = $mysqli->prepare("SELECT PasswordID, Password FROM Passwords ORDER BY `PasswordID` ASC"))){
						echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
					}

					if(!$stmt->execute()){
						echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
					}
					if(!$stmt->bind_result($PasswordID, $Password)){
						echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
					}
					while($stmt->fetch()){
					 echo "<tr>\n<td>\n" . $PasswordID . "\n</td>\n<td>\n" . $Password . "\n</td>\n</tr>";
					}
					$stmt->close();
					?>
				</table>
			</div>
		</body>
	</html>
