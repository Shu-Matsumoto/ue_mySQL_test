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
    $sql = 'INSERT INTO mysqltest_usertable(id, userName, password) VALUES(NULL, :userName, :password)';
    $stmt = $dbh -> prepare($sql);
    //$stmt ->bindParam(':myText', $data["myText"],PDO::PARAM_STR);// bindParamだと値をバインドできなかった。理由は未調査
    $stmt->bindValue(':userName', $data["userName"], PDO::PARAM_STR);
    $stmt->bindValue(':password', $data["password"], PDO::PARAM_STR);
    $stmt ->execute();
     
    // Jsonデータをエンコードして返す
    header('Content-Type: application/json');
    echo json_encode($data);
}
?>