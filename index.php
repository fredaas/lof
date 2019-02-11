<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8" />
    <title>Films</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" type="text/css" media="screen" href="style.css" />
</head>

<body>
<div id="wrapper-outer">
    <div id="page-title">List of Films</div>
    <input id="search" type="text" placeholder="Search table">
</div>

<?php
    include "film-list.html";
?>
</body>

<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
<script src="sort_table.js"></script>
<script src="search_table.js"></script>

</html>
