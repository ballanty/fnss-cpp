#include "quantity.h"

#include <sstream>
#include <regex>

namespace fnss {

Quantity::Quantity(const double &value_, const std::string &unit_,
					const MeasurementUnit &converter_) :
	value(value_), unit(unit_), converter(converter_) {}

Quantity::Quantity(const double &value_, const MeasurementUnit &converter_) :
	value(value_), unit(converter_.getBaseUnit()), converter(converter_) {}

Quantity::Quantity(const std::string &str, const MeasurementUnit &converter_) :
	converter(converter_) {
	this->fromString(str);
}

Quantity::Quantity(const MeasurementUnit &converter_) :
	value(0), unit(converter_.getBaseUnit()), converter(converter_) {}

void Quantity::fromString(const std::string &str) {

	std::string regexpstr = "([0-9]+)(\\.[0-9]*)? *([^ \t]*)";
	std::regex reg(regexpstr);
	std::smatch match;
	std::regex_search(str, match, reg);

	if (!match.empty()) {
		this->value = std::stod(match[1].str() + match[2].str());
		this->unit = match[3];
	} else {
		this->value = 0.0;
		this->unit = "";
	}

	if(this->unit == "")
		this->unit = this->converter.getBaseUnit();
}

std::string Quantity::toString(const std::string &separator) const {
	std::ostringstream ss;
	ss<<this->value;
	return ss.str() + separator + this->unit;
}

void Quantity::convert(const std::string &unit_) {
	this->value *= this->converter.convert(this->unit, unit_);
	this->unit = unit_;
}

double Quantity::getValue() const {
	return this->value;
}

void Quantity::setValue(const double &value_) {
	this->value = value_;
}

std::string Quantity::getUnit() const {
	return this->unit;
}

void Quantity::setUnit(const std::string &unit_) {
	this->unit = unit_;
}

const MeasurementUnit& Quantity::getMeasurementUnit() const {
	return this->converter;
}

Quantity& Quantity::operator=(const Quantity &other) {
	if(this->converter.getBaseUnit() != other.getMeasurementUnit().getBaseUnit())
		throw MeasurementUnit::BaseMismatchException(this->converter.getBaseUnit(),
										other.getMeasurementUnit().getBaseUnit());
	this->value = other.value;
	this->unit = other.unit;

	return *this;
}

bool Quantity::operator<(const Quantity &other) const {
	return this->value * this->converter.convert(this->unit) <
			other.value * this->converter.convert(other.unit);
}

bool Quantity::operator<=(const Quantity &other) const {
	return this->value * this->converter.convert(this->unit) <=
			other.value * this->converter.convert(other.unit);
}

bool Quantity::operator>(const Quantity &other) const {
	return this->value * this->converter.convert(this->unit) >
			other.value * this->converter.convert(other.unit);
}

bool Quantity::operator>=(const Quantity &other) const {
	return this->value * this->converter.convert(this->unit) >=
			other.value * this->converter.convert(other.unit);
}

bool Quantity::operator==(const Quantity &other) const {
	return this->value * this->converter.convert(this->unit) ==
			other.value * this->converter.convert(other.unit);
}

} //namespace
