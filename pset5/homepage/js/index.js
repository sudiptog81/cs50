/**
 * PSet 5 - Homepage
 * Written by Sudipto Ghosh for CS50
 */

// code to redirect programmatically

const githubBtn = document.getElementById("gh");
const instagramBtn = document.getElementById("ig");
const facebookBtn = document.getElementById("fb");
const twitterBtn = document.getElementById("tw");

const handleRedirects = url => {
    window.open(url, "_blank");
}

githubBtn.addEventListener("click", () => handleRedirects("https://github.com/sudiptog81"));
instagramBtn.addEventListener("click", () => handleRedirects("https://instagram.com/sudipto_ghosh.99"));
facebookBtn.addEventListener("click", () => handleRedirects("https://facebook.com/sudiptoghosh99"));
twitterBtn.addEventListener("click", () => handleRedirects("https://twitter.com/ScientificGhosh"));
