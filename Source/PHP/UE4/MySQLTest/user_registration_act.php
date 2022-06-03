<?php
// POSTデータの取得
$json = file_get_contents('php://input');
 
if(!empty($json))
{
    // Json文字列をデーコード
    $data = json_decode($json, true);
     
    // データベースに登録
    $dbh = new PDO('mysql:host=localhost;dbname=ue4db;charset=utf8mb4' ,'root', '');
    //$sql = 'insert into sample (mysqltest_usertable) values (:mytext)' ;
    $sql = 'INSERT INTO mysqltest_usertable(id, myText) VALUES(NULL, :myText)';
    $stmt = $dbh -> prepare($sql);
    //$stmt ->bindParam(':myText', $data["myText"],PDO::PARAM_STR);
    $stmt->bindValue(':myText', $data["myText"], PDO::PARAM_STR);
    $stmt ->execute();
     
    // Jsonデータをエンコードして返す
    header('Content-Type: application/json');
    echo json_encode($data);
}
?>