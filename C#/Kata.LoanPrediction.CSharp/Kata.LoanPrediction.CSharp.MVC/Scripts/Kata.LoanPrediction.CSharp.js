﻿jQuery.validator.setDefaults({
    highlight: function (element, errorClass, validClass) {
        if (element.type === 'radio') {
            this.findByName(element.name).addClass(errorClass);
        } else {
            $(element).closest('.form-group').addClass('has-error');
        }
    },
    unhighlight: function (element, errorClass, validClass) {
        if (element.type === 'radio') {
            this.findByName(element.name).removeClass(errorClass);
        } else {
            $(element).closest('.form-group').removeClass('has-error');
        }
    }
});

$(function () {

    $("span.field-validation-valid, span.field-validation-error").addClass('help-block');
    $("div.form-group").has("span.field-validation-error").addClass('has-error');
    $("div.validation-summary-errors").has("li:visible").addClass("alert alert-block alert-danger");

});

$(document).ready(function () {
    $(".combodate").combodate(
    {
        minYear: 1975,
        maxYear: 2050,
        customClass: "form-control"
    });
});




