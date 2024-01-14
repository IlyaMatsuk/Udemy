const express = require('express');

const app = express();

app.get('/', (req, res) => {
  res.send(`
    <h1>Nice to see you here! Well done! I love you, Ogonek! </h1>
  `);
})

app.listen(3000);