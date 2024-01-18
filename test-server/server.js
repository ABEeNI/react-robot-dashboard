const express = require('express');
const bodyParser = require('body-parser');

const app = express();
const port = 5432; 

app.use(bodyParser.json()); 

app.post('/capture', (req, res) => {
  console.log('Received data:', req.body);
  res.status(200).send('Data received fasziii');
});

app.get('/status', (req, res) => {
    console.log('Received data:');
    res.send('Server is up and running');
  });

app.listen(port, () => {
  console.log(`Listening for requests on http://localhost:${port}`);
});
