<html>
<body>
<h1> Online-Server für den RoboDyn2560 </h1>
<h2> </h2>
</body>
</html>

<?php

//EINFÜGEN: Zugangsdaten zur Datenbank
$username = '';
$password = '';
$db = '';
//***                               ****


if ($_GET){
$pdo = new PDO('mysql:host=localhost;dbname=' . $db, $username, $password);

	if ($_GET['cmd'] == 'wetter'){
		$url = 'http://192.241.187.136/data/2.5/weather?q=10407,de&appid=b8e4efa1fc516cf06fd0f9588282d655&units=metric';
		$curl = curl_init ();
		curl_setopt ($curl, CURLOPT_URL, $url);
		curl_setopt ($curl, CURLOPT_TIMEOUT, 15);
		curl_setopt ($curl, CURLOPT_RETURNTRANSFER, true);
		$json = curl_exec ($curl);
		curl_close ($curl);
		$json = str_replace (',', ':', $json);
		$explodiert = explode (':', $json);
		$temperatur = $explodiert[18];
		$temperatur = str_replace('.', ',', $temperatur);
		$luftfeuchtigkeit = $explodiert[22];
		echo ('|' . $temperatur . '>' . $luftfeuchtigkeit);
	}
	
	if ($_GET['cmd'] == 'steuerung'){
		$sql = 'SELECT * FROM Pending';
		$result = $pdo->query ($sql);
		echo "|+";
		foreach ($result as $row){
			echo $row['data'];
		}
		$sql = "DELETE FROM Pending WHERE screen='no'";
		$pdo->query ($sql);
	}

	if (isset ($_GET['data'])){
		$sql = "INSERT INTO Pending (data) VALUES ('" . $_GET['data'] . "')";
		$pdo->query ($sql);
		echo ($_GET['data'] . ' eingefuegt');
	}

	else if (isset ($_GET['screen'])){
		$sql = "INSERT INTO Pending (screen) VALUES ('" . $_GET['screen'] . "')";
		$pdo->query ($sql);
	}
}

?>
