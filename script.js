// Sample movie database
const movies = [
    { title: "The Shawshank Redemption", genre: "Drama" },
    { title: "The Godfather", genre: "Crime" },
    { title: "The Dark Knight", genre: "Action" },
    { title: "Pulp Fiction", genre: "Crime" },
    { title: "Forrest Gump", genre: "Drama" },
    { title: "Inception", genre: "Sci-Fi" },
    { title: "The Matrix", genre: "Sci-Fi" },
    { title: "The Lord of the Rings", genre: "Fantasy" },
    { title: "Avatar", genre: "Sci-Fi" }
];

document.getElementById('preferencesForm').addEventListener('submit', function(event) {
    event.preventDefault(); // Prevent form submission

    const genre = document.getElementById('genre').value.trim().toLowerCase();
    const recommendations = getRecommendations(genre);

    displayRecommendations(recommendations);
});

function getRecommendations(preferredGenre) {
    return movies.filter(movie => movie.genre.toLowerCase() === preferredGenre);
}

function displayRecommendations(recommendations) {
    const recommendationsDiv = document.getElementById('recommendations');
    recommendationsDiv.innerHTML = ''; // Clear previous recommendations

    if (recommendations.length === 0) {
        recommendationsDiv.innerHTML = '<p>No recommendations found for this genre.</p>';
    } else {
        recommendationsDiv.innerHTML = '<h2>Recommended Movies:</h2><ul>' +
            recommendations.map(movie => `<li>${movie.title}</li>`).join('') +
            '</ul>';
    }
}
