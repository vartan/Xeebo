var express = require('express');
var app = express();
//app.set('view engine', 'jade');
app.get('/test', function(req, res) {
    res.sendfile('views/test.html', {root: __dirname })
});
app.use(express.static(process.cwd() + '/public'));

app.get('/api', function(req, res){
  res.send('hello world');
});

var listenPort = process.env.XEEBO_PORT || 8080;
app.listen(listenPort);