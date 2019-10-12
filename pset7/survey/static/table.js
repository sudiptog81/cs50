/**
 * PSet 7.2 - Survey
 * Written by Sudipto Ghosh for CS50
 */

// wait for DOM to finish loading
$(document).ready(() => {
    // initialise DataTable
    $("#table").DataTable({
        searching: false,
        paging: false,
        info: false
    });
});
