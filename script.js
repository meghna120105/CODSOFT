// Ensure the face-api.js models are loaded
async function loadModels() {
    const MODEL_URL = '/models';
    await faceapi.nets.ssdMobilenetv1.loadFromUri(MODEL_URL);
    await faceapi.nets.faceLandmark68Net.loadFromUri(MODEL_URL);
    await faceapi.nets.faceRecognitionNet.loadFromUri(MODEL_URL);
}

// Handle image input and face detection
async function handleImageUpload(event) {
    const image = await faceapi.bufferToImage(event.target.files[0]);
    const canvas = document.getElementById('canvas');
    const displaySize = { width: image.width, height: image.height };
    faceapi.matchDimensions(canvas, displaySize);
    const detections = await faceapi.detectAllFaces(image).withFaceLandmarks().withFaceDescriptors();
    const resizedDetections = faceapi.resizeResults(detections, displaySize);
    canvas.getContext('2d').clearRect(0, 0, canvas.width, canvas.height);
    faceapi.draw.drawDetections(canvas, resizedDetections);
    faceapi.draw.drawFaceLandmarks(canvas, resizedDetections);
    document.getElementById('caption').textContent = `Detected ${detections.length} face(s)`;
}

// Set up the event listener for image input
document.getElementById('imageInput').addEventListener('change', handleImageUpload);

// Load models and initialize the app
loadModels().then(() => {
    console.log('Face-api.js models loaded');
});
