<?php require_once "header.php"; ?>
<?php 
if(isset($_POST['login'])){
    require "db.php";
    $email = mysqli_real_escape_string($db,trim($_POST['email']));
    $password = mysqli_real_escape_string($db,trim($_POST['password']));
    $password=MD5("some".$password."text");
    
    $checkIfExists = mysqli_query($db,"SELECT * FROM users WHERE email = '$email' AND password= '$password'");

    if(mysqli_num_rows($checkIfExists)){
    	$row = mysqli_fetch_assoc($checkIfExists);
    	$_SESSION['user']=$row['email'];
    	$_SESSION['user_id']=$row['user_id'];
    }
    header("location: index.php");
}
?>
<div class="row">
<?php
if(isset($_SESSION['registerMessage'])){
    $alertColorClass = $_SESSION['registerMessage']=="წარმატებით დარეგისტრირდით" ? "alert alert-success" : "alert alert-danger";
    $messageDiv = <<<DELIMITER
<div class="{$alertColorClass}">{$_SESSION['registerMessage']}</div>
DELIMITER;
    echo $messageDiv;
    unset($_SESSION['registerMessage']);
}
?>
    <div class="col-sm-4 col-sm-offset-4">
        <form action="" method="post">
            <div class="form-group text-center">
                <label for="email">Email</label>
                <input class="form-control" name="email" type="email" value="" required/>
            </div>

            <div class="form-group text-center">
                <label for="password">პაროლი</label>
                <input class="form-control" name="password" type="password" value="" required/>
            </div>
            <div class="form-group text-center">
                <button type="submit" class="btn btn-success btn-lg" name="login">შესვლა</button>
            </div>
        </form>
    </div>
</div>
<?php require_once "footer.php"; ?>