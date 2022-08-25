#ifndef __HUBBART_HUBBART_EXCEPTION_HPP
#define __HUBBART_HUBBART_EXCEPTION_HPP

#include <exception>
#include <string>

/**
 * @brief The default Hubbart Lexer exception
 * 
 */
class HubbartException: std::exception {
private:
    std::string entity;
    std::string message;

public:
    /**
     * @brief Construct a new Lexer Exception object
     * 
     */
    HubbartException(const std::string &, const std::string &);

    /**
     * @brief Get the Message object
     * 
     * @return std::string 
     */
    std::string getMessage(void);

    /**
     * @brief 
     * 
     */
    std::string getEntity(void);
};

#endif