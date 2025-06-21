#!/usr/bin/node

const request = require('request');

if (process.argv.length < 3) {
  console.error('Usage: ./0-starwars_characters.js <movie_id>');
  process.exit(1);
}

const movieId = process.argv[2];
const apiUrl = `https://swapi-api.alx-tools.com/api/films/${movieId}/`;

request(apiUrl, (err, res, body) => {
  if (err) return console.error(err);
  if (res.statusCode !== 200) return console.error(`Error: ${res.statusCode}`);

  const film = JSON.parse(body);
  const characters = film.characters;

  characters.forEach((url) => {
    request(url, (err, res, body) => {
      if (!err && res.statusCode === 200) {
        const character = JSON.parse(body);
        console.log(character.name);
      }
    });
  });
});
