#!/usr/bin/node

const request = require('request');

// Convert request into a promise for easier use with async/await
function fetch(url) {
  return new Promise((resolve, reject) => {
    request(url, (err, res, body) => {
      if (err) reject(err);
      else if (res.statusCode !== 200) reject(new Error(`Status code: ${res.statusCode}`));
      else resolve(JSON.parse(body));
    });
  });
}

async function printCharacters(movieId) {
  try {
    const film = await fetch(`https://swapi-api.alx-tools.com/api/films/${movieId}/`);
    for (const characterURL of film.characters) {
      const character = await fetch(characterURL);
      console.log(character.name);
    }
  } catch (error) {
    console.error(error.message);
  }
}

if (process.argv.length < 3) {
  console.error('Usage: ./0-starwars_characters.js <movie_id>');
  process.exit(1);
}

printCharacters(process.argv[2]);
