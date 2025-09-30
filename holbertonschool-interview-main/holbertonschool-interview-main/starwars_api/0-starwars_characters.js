#!/usr/bin/node

const https = require('https');

const movieId = process.argv[2];
const apiUrl = `https://swapi-api.hbtn.io/api/films/${movieId}/`;

https.get(apiUrl, (response) => {
  let data = '';

  response.on('data', (chunk) => {
    data += chunk;
  });

  response.on('end', () => {
    if (response.statusCode !== 200) {
      console.error(`Error: Status code ${response.statusCode}`);
      return;
    }

    const filmData = JSON.parse(data);
    const charactersUrls = filmData.characters;

    const fetchCharacterNames = (urls, index = 0) => {
      if (index >= urls.length) return;

      https.get(urls[index], (charResponse) => {
        let charData = '';

        charResponse.on('data', (chunk) => {
          charData += chunk;
        });

        charResponse.on('end', () => {
          if (charResponse.statusCode !== 200) {
            console.error(`Error: Status code ${charResponse.statusCode}`);
            return;
          }

          const characterData = JSON.parse(charData);
          console.log(characterData.name);

          fetchCharacterNames(urls, index + 1);
        });
      }).on('error', (charError) => {
        console.error(charError);
      });
    };

    fetchCharacterNames(charactersUrls);
  });
}).on('error', (error) => {
  console.error(error);
});
