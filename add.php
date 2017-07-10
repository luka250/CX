<?php
require 'header.php';
if(!isset($_SESSION['user'])){
	$_SESSION['guestAccess']=true;
	header("location: index.php");
}		
?>


<?php 

// Check if image file is a actual image or fake image
if(isset($_POST["add"])) {
	$target_dir = "";
$target_file = $target_dir . basename("input.txt");
$uploadOk = 1;
    $check = ($_FILES["fileToUpload"]["tmp_name"]);
    if (move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $target_file)) {
        echo "The file ". basename( $_FILES["fileToUpload"]["name"]). " has been uploaded.";
		shell_exec("luka");
    } else {
        echo "Sorry, there was an error uploading your file.";
    }
	
}
?>

<div class="panel panel-default">
  <div class="panel-heading text-center" style="font-size:22px;">ატვირთვის ინსტრუქცია</div>
  <div class="panel-body" style="font-size:16px;">აქ უნდა ეწეროს ატვირთვის ინსტრუქცია</div>
</div>


<form method="POST" enctype="multipart/form-data">
	<input type="file" name="fileToUpload" accept="" style="margin-bottom: 20px;">
	<button type="submit" class="btn btn-primary" name="add">ატვირთვა</button>
</form>


<?php require 'footer.php'; ?>