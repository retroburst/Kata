var kataLoanPredictionView = function() {
    var templates = null;
    var validateConstraints = null;
    var defaultLoanContextSettings = {
        startDate : moment(),
        targetEndDate : moment().add(25, 'year'),
        balance : 250000,
        interestRate : 5.00,
        minRepaymentAmount : 2000,
        minRepaymentDay : 1,
        extraRepaymentAmount : 1000,
        extraRepaymentDay : 20,
        currencySymbol : accounting.settings.currency.symbol
    };
    
    ///////////////////////////////////////////////////////
    // constants
    var kataLoanPredictionViewConstants = function() {
        var constants = {
            DATE_FORMAT : "DD/MM/YYYY"
        };
        
        return ({
            get: function(constantName) {
                return (constants[constantName]);
            }
        });
    }();
    
    var joinErrorMessages = function(messages){
        messages = messages || [];
        var result = messages.join('. ');
        if(!S(result).endsWith('.')){
            result += '.';
        }
        return(result);
    };
    
    var showValidationErros = function showValidationErros(errors){
        errors = errors || {};
        for (var property in errors) {
            console.log("Property");
            console.log(property);
            if (errors.hasOwnProperty(property)) {
                var input = $('#' + property);
                console.log(input);
                if(input){
                    var group = input.closest('.form-group');
                    if(group){
                        group.addClass('has-error');
                        group.find('.validation-message').text(joinErrorMessages(errors[property]));
                    }
                }
            }
        }
    };
    
    var clearValidationErrors = function clearValidationErrors(){
        $('.validation-message').empty();
        $('.form-group').removeClass('has-error');
    };
    
    var initHandlebars = function initHandlebars(){
        Handlebars.registerHelper('formatDate', function(date) {
            var dateAsMoment = date;
            if(date instanceof Date){
                dateAsMoment = moment(date);
            }
            if(dateAsMoment instanceof moment){
                return(moment(date).format(kataLoanPredictionViewConstants.get("DATE_FORMAT")));
            }
        });
        
        Handlebars.registerHelper('formatMoney', function(amount) {
            if(!isNaN(amount)){
                return(accounting.formatMoney(amount));
            }
        });
        
        Handlebars.registerHelper('formatDecimal', function(target) {
            if(!isNaN(target)){
                return(target.toFixed(2));
            }
        });
        
        Handlebars.registerHelper('isAroundTargetEndDate',function isAroundTargetEndDate(transDate, targetEndDate){
            var transDateAsMoment = moment(transDate);
            var targetEndDateAsMoment = moment(targetEndDate);
            if(transDateAsMoment.month() == targetEndDateAsMoment.month()
                && transDateAsMoment.year() == targetEndDateAsMoment.year()){
                return(true);
            } else {
                return(false);
            }
        });

        Handlebars.registerHelper('formatDateForComboDate', function(date) {
            var dateAsMoment = date;
            if(date instanceof Date){
                dateAsMoment = moment(date);
            }
            if(dateAsMoment instanceof moment){
                return(dateAsMoment.format(kataLoanPredictionViewConstants.get("DATE_FORMAT")));
            }
        });
        
        Handlebars.registerHelper('safePrintParameter', function(target) {
            if(target){
                return(target);
            } else {
                return('N/A');
            }
        });

        var templates = {
            inputFormTemplate : Handlebars.compile($("#input-form-template").html()),
            resultsTemplate : Handlebars.compile($("#results-template").html())
        };
        return(templates);
    };
    
    // init form
    var initInputForm = function initInputForm(){
        var initialSettings = defaultLoanContextSettings || storedSettings;
        // intial view setup
        $('#inputContainer').show();
        $('#resultsContainer').hide();
        $('#inputFormContainer').empty();
        $('#inputFormContainer').append(templates.inputFormTemplate(initialSettings));
        
        $('#calculateButton').click(function(e){
            clearValidationErrors();
            var attributes = {};
            attributes.balance = $('#balance').val();
            attributes.interestRate = $('#interestRate').val();
            attributes.minRepaymentAmount = $('#minRepaymentAmount').val();
            attributes.minRepaymentDay = $('#minRepaymentDay').val();
            attributes.extraRepaymentAmount = $('#extraRepaymentAmount').val();
            attributes.extraRepaymentDay = $('#extraRepaymentDay').val();
            attributes.startDate = $('#startDate').val();
            attributes.targetEndDate = $('#targetEndDate').val();
            var errors = validate(attributes, validateConstraints);
            console.log(errors);
            if(!errors){
                initResults();
            } else {
                showValidationErros(errors);
            }
        });
        
        $('.combodate').combodate(
            {
            minYear: 1975,
            maxYear: 2050,
            customClass: 'form-control combodate-inline',
            format: kataLoanPredictionViewConstants.get("DATE_FORMAT")
        });
    };
    
    var initResults = function initResults(){
        // calculate
        var context = new kataLoanPredictionCommon.models.loanContext();
        context.balance = parseFloat($('#balance').val());
        context.interestRate = parseFloat($('#interestRate').val());
        context.minRepaymentAmount = parseFloat($('#minRepaymentAmount').val());
        context.minRepaymentDay = parseInt($('#minRepaymentDay').val());
        context.extraRepaymentAmount = parseFloat($('#extraRepaymentAmount').val());
        context.extraRepaymentDay = parseInt($('#extraRepaymentDay').val());
        context.startDate = moment($('#startDate').val(), kataLoanPredictionViewConstants.get("DATE_FORMAT")).toDate();
        context.targetEndDate = moment($('#targetEndDate').val(), kataLoanPredictionViewConstants.get("DATE_FORMAT")).toDate();
        var output = kataLoanPredictionCommon.calculator.calculate(context);
        // clear table
        $('#resultsContainer').empty();
        $('#resultsContainer').append(templates.resultsTemplate({ context : context, output : output }));
        // show results
        // hide input
        $('#resultsContainer').show();
        $('#inputContainer').hide();
        
        $('.start-over-button').click(function(e){
            initInputForm();
        });
        
        $("html, body").animate({ scrollTop: 0 }, "slow");
    };
    
    var initValidate = function initValidate(){
        // Before using it we must add the parse and format functions
        // Here is a sample implementation using moment.js
        validate.extend(validate.validators.datetime, {
            // The value is guaranteed not to be null or undefined but otherwise it
            // could be anything.
            parse: function(value, options) {
                return +moment.utc(value, kataLoanPredictionViewConstants.get("DATE_FORMAT"));
            },
            // Input is a unix timestamp
            format: function(value, options) {
                var format = options.dateOnly ? kataLoanPredictionViewConstants.get("DATE_FORMAT") : kataLoanPredictionViewConstants.get("DATE_FORMAT") + " hh:mm:ss";
                return moment.utc(value).format(format);
            }
        });
        
        // These are the constraints used to validate the form
        var constraints = {
            startDate: {
                presence: true,
                datetime: {
                    dateOnly: true
                }
            },
            targetEndDate: {
                presence: true,
                datetime: {
                    dateOnly: true
                }
            },
            balance: {
                presence: true,
                numericality: {
                    onlyInteger: false,
                    greaterThan: 0
                }
            },
            interestRate: {
                presence: true,
                numericality: {
                    onlyInteger: false,
                    greaterThan: 0
                }
            },
            minRepaymentAmount: {
                presence: true,
                numericality: {
                    onlyInteger: false,
                    greaterThan: 0
                }
            },
            minRepaymentDay: {
                presence: true,
                numericality: {
                    onlyInteger: true,
                    greaterThan: 0
                }
            },
            extraRepaymentAmount: {
                presence: false,
                numericality: {
                    onlyInteger: false,
                    greaterThan: 0
                }
            },
            extraRepaymentDay: {
                presence: false,
                numericality: {
                    onlyInteger: true,
                    greaterThan: 0
                }
            }
        };
        return(constraints);
    };

    var initView = function initVew(){
        // init handlebars
        templates = initHandlebars();
        validateConstraints = initValidate();
        initInputForm();
    };
    
    ///////////////////////////////////////////////////////
    // returns public interface
    return ({
        initView : initView
    });
}();