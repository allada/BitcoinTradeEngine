<?php
$data = file("/root/btct.password");
$config = array();
foreach($data as $d){
	$d = preg_split('/\s+/', $d, 3);
	$config[$d[1]] = stripcslashes(substr($d[2], 1, -2));
}

$m = new MongoClient("mongodb://{$config['MONGO_USER']}:{$config['MONGO_PASSWORD']}@{$config['MONGO_IP']}", array('db' => $config['MONGO_SOURCE']));
try{
	$m->btct->orders->drop();
}catch(Exception $e){}
try{
	$m->btct->currencies->drop();
}catch(Exception $e){}
try{
	$m->btct->markets->drop();
}catch(Exception $e){}
try{
	$m->btct->transactions->drop();
}catch(Exception $e){}

$currencies = $m->selectCollection('btct', 'currencies');
$markets = $m->selectCollection('btct', 'markets');

$currencies->insert(array(
	'_id' => 0,
	'name' => 'usd'
));
$currencies->insert(array(
	'_id' => 1,
	'name' => 'btc'
));

$markets->insert(array(
	'_id' => 1,
	'c1' => 'usd',
	'c2' => 'btc',
));
