#include <memory>
#include <string>
#include <iostream>
#include <cstdlib> // for system()
#include <cstdint> // for uint32_t
#include <chrono>  // for currentYear() and currentDate() implementation

//------------------- User includes ----------------------------

// A class that represents a form.
// As you will see below: many fields and many validators can be added to the form
#include "Form.h"

// A class that represents a field. 
// As you will see below: (at least) one validator can be added to each field 
#include "Field.h"

 //A class that represents a Date (YYYY-MM-DD).
 //The class must override the << and >> operators to read/print the date format,
 //and handle basic format validation.
#include "Date.h"

// A class that represents a range validator.
// It validates if a field value is in some range.
// The type used as template parameter must implement >= and <= operators.
#include "RangeValidator.h"

// A class that validates a name format.
// Ensures the name does not contain digits.
#include "NameValidator.h"

// A class that represents an ID validator.
// ID validation is done using the control digit.
// Works only on the type 'uint32_t'.
#include "IdValidator.h"

// A class that represents an Email validator.
// It validates that the email format is valid (user_name@domain_name.top-level_domain).
#include "MailValidator.h"

// A class that represents a Vacation Date validator.
// Validates that the date is strictly in the future and within the current calendar year.
#include "VacationDateValidator.h"

// A class that represents a value and its name.
// The class must override the << and >> operators.
// >> operator reads an int and << operator prints the string value (e.g., Vacation type or Hosting type)
// if the value is valid, and if not - the number.
#include "ValuesToNames.h"

// A class that keeps the names of the different vacation types (Weekend / Mid-week)
#include "VacationTypes.h"

// A class that keeps the names of the different hosting types (Breakfast / Half board / Full board)
#include "HostingTypes.h"

// A class that represents a vacation-type-vs.-hosting-type validator.
// It checks if the vacation type and hosting type supplied match each other.
// The types used as template parameter must be Field.
#include "VacationToHostingValidator.h"

// A class that represents a vacation-type-vs.-nights validator.
// It checks if the vacation type and number of nights match each other.
// The types used as template parameter must be Field.
#include "VacationToNightsValidator.h"

// A class that represents a capacity validator.
// It checks if the total people matches adults+kids, and fits in the selected rooms.
#include "CapacityValidator.h"

//------------------- Function declarations ----------------------------

// Gets the welcome message
std::string getWelcomeMessage();

// Gets the goodbye message
std::string getGoodbyeMessage();

// Gets the error message
std::string getErrorMessage();

// Utility function for clearing the terminal screen
void clearScreen();

 //Utility function for getting current date from computer clock in Data object
Date currentDate();

//------------------- consts --------------------------

constexpr int MIN_AGE          = 18;
constexpr int MAX_AGE          = 120;
constexpr int FAMILI_ROOMS_NUM = 15;
constexpr int PAIR_ROOMS_NUM   = 15;
constexpr int MAX_NIGHTS       = 30;

const std::string ageErrMsg          = "Age must be between " + std::to_string(MIN_AGE) + " and " + std::to_string(MAX_AGE) + " years old.";
const std::string vacationTypeErrMsg = "Invalid vacation type selected.";
const std::string hostingTypeErrMsg  = "Invalid hosting type selected.";
const std::string nightsErrMsg       = "Number of nights must be between 1 and " + std::to_string(MAX_NIGHTS) + ".";
const std::string pairRoomsErrMsg    = "Pair rooms must be between 0 and " + std::to_string(PAIR_ROOMS_NUM) + ".";
const std::string familyRoomsErrMsg  = "Family rooms must be between 0 and " + std::to_string(FAMILI_ROOMS_NUM) + ".";
const std::string maxPeopleErrMsg    = "Number of people must be positive (at least 1) and fit hotel capacity.";
const std::string adultsNumErrMsg    = "At least 1 adult is required, up to maximum hotel capacity.";
const std::string kidsNumErrMsg      = "Number of children cannot be negative and must fit hotel capacity.";

//------------------- main ----------------------------

int main()
{
	// Creating the form fields
	auto nameField         = std::make_unique<Field<std::string>>("What is your name?");
	auto idField           = std::make_unique<Field<uint32_t>>   ("What is your ID?");
	auto mailField         = std::make_unique<Field<std::string>>("What is your email address?");
	auto dateOfBirthField  = std::make_unique<Field<Date>>       ("What is your date of birth? (YYYY-MM-DD)");
	auto vacationDateField = std::make_unique<Field<Date>>       ("What is the date on which you wish to start your vacation? (YYYY-MM-DD)");

	auto vacationTypes     = ValuesToNames<VacationTypes>();
	auto vacationTypeField = std::make_unique<Field<
		                             ValuesToNames<VacationTypes>>>("What is your desired vacation type?\n" + vacationTypes.valuesAndNames());
	
	auto hostingTypes      = ValuesToNames<HostingTypes>();
	auto hostingTypeField  = std::make_unique<Field<
		                              ValuesToNames<HostingTypes>>>("What is your desired hosting type?\n" + hostingTypes.valuesAndNames());
	
	auto nightsNumField    = std::make_unique<Field<int>>        ("How many nights do you wish to book?");
	auto pairRoomsField    = std::make_unique<Field<int>>        ("How many pair rooms do you want?");
	auto familyRoomsField  = std::make_unique<Field<int>>        ("How many family rooms do you want?");
	auto totalPeopleField  = std::make_unique<Field<int>>        ("How many people are in your reservation?");
	auto adultsField       = std::make_unique<Field<int>>        ("Number of adults?");
	auto kidsField         = std::make_unique<Field<int>>        ("Number of children?");

	// Creating the field validators
	auto nameValidator         = std::make_unique<NameValidator>();
	auto idValidator           = std::make_unique<IdValidator>();
	auto mailValidator         = std::make_unique<MailValidator>();
	auto ageValidator          = std::make_unique<RangeValidator<Date>>(currentDate() - MAX_AGE,currentDate() - MIN_AGE, ageErrMsg);
	auto vacationDateValidator = std::make_unique<VacationDateValidator>(currentDate());
	auto vacationTypeValidator = std::make_unique<RangeValidator<ValuesToNames<VacationTypes>>>(1, 2, vacationTypeErrMsg);
	auto hostingTypeValidator  = std::make_unique<RangeValidator<ValuesToNames<HostingTypes>>>(1, 3, hostingTypeErrMsg);
	auto nightsValidator       = std::make_unique<RangeValidator<int>>(1, MAX_NIGHTS, nightsErrMsg);
	auto pairRoomsValidator    = std::make_unique<RangeValidator<int>>(0, PAIR_ROOMS_NUM, pairRoomsErrMsg);
	auto familyRoomsValidator  = std::make_unique<RangeValidator<int>>(0, FAMILI_ROOMS_NUM, familyRoomsErrMsg);
	auto peopleValidator       = std::make_unique<RangeValidator<int>>(1, FAMILI_ROOMS_NUM * 5 + PAIR_ROOMS_NUM * 2, maxPeopleErrMsg);
	auto adultsValidator       = std::make_unique<RangeValidator<int>>(1, FAMILI_ROOMS_NUM * 5 + PAIR_ROOMS_NUM * 2, adultsNumErrMsg);
	auto kidsValidator         = std::make_unique<RangeValidator<int>>(0, FAMILI_ROOMS_NUM * 5 + PAIR_ROOMS_NUM * 2 - 1, kidsNumErrMsg);


	// Adding the validators to the fields
	nameField          ->addValidator(nameValidator.get());
	idField            ->addValidator(idValidator.get());
	mailField          ->addValidator(mailValidator.get());
	dateOfBirthField   ->addValidator(ageValidator.get());
	vacationDateField  ->addValidator(vacationDateValidator.get());
	vacationTypeField  ->addValidator(vacationTypeValidator.get());
	hostingTypeField   ->addValidator(hostingTypeValidator.get());
	nightsNumField     ->addValidator(nightsValidator.get());
	pairRoomsField     ->addValidator(pairRoomsValidator.get());
	familyRoomsField   ->addValidator(familyRoomsValidator.get());
	totalPeopleField   ->addValidator(peopleValidator.get());
	adultsField        ->addValidator(adultsValidator.get());
	kidsField          ->addValidator(kidsValidator.get());

	// Creating form validators
	auto vacationToHostingValidator = std::make_unique<VacationToHostingValidator<Field<ValuesToNames<VacationTypes>>,
		                                 Field<ValuesToNames<HostingTypes>>>>(vacationTypeField.get(), hostingTypeField.get());

	auto vacationToNightsValidator  = std::make_unique<VacationToNightsValidator<Field<ValuesToNames<VacationTypes>>, 
		                                 Field<int>>>(vacationTypeField.get(), nightsNumField.get());

	auto capacityValidator          = std::make_unique<CapacityValidator>(totalPeopleField.get(), adultsField.get(), 
		                                 kidsField.get(), pairRoomsField.get(), familyRoomsField.get());

	// Creating the form and adding the fields to it
	auto myForm = Form();
	myForm.addField(nameField.get());
	myForm.addField(idField.get());
	myForm.addField(mailField.get());
	myForm.addField(dateOfBirthField.get());
	myForm.addField(vacationDateField.get());
	myForm.addField(vacationTypeField.get());
	myForm.addField(hostingTypeField.get());
	myForm.addField(nightsNumField.get());
	myForm.addField(pairRoomsField.get());
	myForm.addField(familyRoomsField.get());
	myForm.addField(totalPeopleField.get());
	myForm.addField(adultsField.get());
	myForm.addField(kidsField.get());

	// Adding form validators
	myForm.addValidator(vacationToHostingValidator.get());
	myForm.addValidator(vacationToNightsValidator.get());
	myForm.addValidator(capacityValidator.get());

	// Getting the information from the user
	clearScreen();
	std::cout << getWelcomeMessage();

	// Get the input only for empty or not valid fields
	myForm.fillForm();

	// Validation loop
	for (auto formIsCorrect = myForm.validateForm(); !formIsCorrect; formIsCorrect = myForm.validateForm())
	{
		// Displays all form fields with value (and error if not valid)
		clearScreen();
		std::cout << getErrorMessage();
		std::cout << myForm << '\n';

		myForm.fillForm();
	}

	clearScreen();
	std::cout << getGoodbyeMessage();
	std::cout << myForm << '\n';
	return 0;
}

std::string getWelcomeMessage()
{
	return 
		"+----------------------------------------------------------+\n"
		"|                    Hello and welcome!                    |\n"
		"|     In order to book please fill in the fields below     |\n"
		"+----------------------------------------------------------+\n";
}

std::string getErrorMessage()
{
	return 
		"+----------------------------------------------------------+\n"
		"|    There was an error in at least one of the fields!     |\n"
		"|               Please correct the error(s)                |\n"
		"+----------------------------------------------------------+\n";
}

std::string getGoodbyeMessage()
{
	return 
		"+----------------------------------------------------------+\n"
		"|                        Thank you!                        |\n"
		"|                This is the data you sent:                |\n"
		"+----------------------------------------------------------+\n";
}

void clearScreen()
{
	system("cls");
}

Date currentDate()
{
	namespace ch = std::chrono;
	auto now = ch::system_clock::now();
	auto ymd = ch::year_month_day(ch::floor<ch::days>(now));

	int year = static_cast<int>(ymd.year());
	unsigned int month = static_cast<unsigned int>(ymd.month());
	unsigned int day = static_cast<unsigned int>(ymd.day());

	// Requires the Date class to have a constructor: Date(int year, int month, int day)
	return Date(year, month, day);
}
