<?php require_once "header.php"; ?>
      <!-- Main component for a primary marketing message or call to action -->
      <?php 
      	if(isset($_SESSION['guestAccess'])){
      		echo "<div class='alert alert-warning alert-dismissable fade in'> <a href='#' class='close' data-dismiss='alert' aria-label='close'>&times;</a>ტესტის დასამატებლად საჭიროა ავტორიზაცია</div>";
      		unset($_SESSION['guestAccess']);
      	}
      ?>
      
      <div class="jumbotron">
        <h1 style="font-size: 40px;">საიტის შესახებ</h1>
        <p style="font-size: 17px;">აქ უნდა იყოს საიტის მოკლე აღწერა</p>
        <p>
          <a class="btn btn-lg btn-primary" href="add.php" role="button">ტესტის დამატება &raquo;</a>
        </p>
      </div>
      <!-- main component area end -->
<?php require_once "footer.php"; ?>