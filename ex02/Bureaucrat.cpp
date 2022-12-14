#include "Bureaucrat.hpp"
#include "Form.hpp"

Bureaucrat::Bureaucrat(): name("Jon Doe"), grade(75)
{
//	std::cout << "[Bureaucrat] Default constructor called\n";
}

Bureaucrat::Bureaucrat(std::string const &name, int grade): name(name), grade(grade)
{
//	std::cout << "[Bureaucrat] constructor called\n";
	if (grade < highestGrade)
		throw (GradeTooHighException());
	if (grade > lowestGrade)
		throw (GradeTooLowException());
}

Bureaucrat::Bureaucrat(const Bureaucrat &src)
{
//	std::cout << "[Bureaucrat] Copy constructor called\n";
	*this = src;
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat &src)
{
//	std::cout << "[Bureaucrat] Copy assignment operator called\n";
	*const_cast<std::string*>(&name) = src.getName();
	grade = src.getGrade();
	return (*this);
}

Bureaucrat::~Bureaucrat()
{
	std::cout << "[Bureaucrat] Destructor called\n";
}

std::ostream& operator<<(std::ostream& outputStream, const Bureaucrat &src)
{
	outputStream << src.getName() << ", bureaucrat grade " << src.getGrade() << ".\n";
	return (outputStream);
}

const std::string &Bureaucrat::getName() const
{
	return (name);
}

int Bureaucrat::getGrade() const
{
	return (grade);
}

void Bureaucrat::incrementGrade()
{
	std::cout << getName() << " is increasing score From " << getGrade() << '\n';
	grade--;
	if (grade < highestGrade)
		throw (GradeTooHighException());
}

void Bureaucrat::decrementGrade()
{
	std::cout << getName() << " is decreasing score From " << getGrade() << '\n';
	grade++;
	if (grade > lowestGrade)
		throw (GradeTooLowException());
}

void Bureaucrat::signForm(Form &src)
{
	try {
		src.beSigned(*this);
		std::cout << this->getName() << " signed " << src.getName() << '\n';
	} catch (const std::exception &e)
	{
		std::cout << this->getName() << " couldn't sign "
		<< src.getName() << " because " << e.what();
	}
}

void Bureaucrat::executeForm(Form const &form)
{
	if (!form.execute(*this))
		std::cout << this->getName() << " executed " << form.getName() << '\n';
	else
		std::cout << this->getName() << " cannot execute " << form.getName() << '\n';
}

const char* Bureaucrat::GradeTooHighException::what(void) const throw()
{
	return "Bureaucrat grade too high!!\n";
}

const char *Bureaucrat::GradeTooLowException::what(void) const throw()
{
	return "Bureaucrat grade too low!!\n";
}
