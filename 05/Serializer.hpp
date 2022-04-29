#pragma once
#include <iostream>
#include <sstream>


enum class Error
{
    NoError,
    CorruptedArchive
};


class Serializer
{
    static constexpr char Separator = ' ';
    std::ostream& out_;

public:

    explicit Serializer(std::ostream& out)
        : out_(out)
    {
    }

    template <class T>
    Error save (T& object)
    {
        return object.serialize(*this);
    }

    template <class... Args>
    Error operator()(Args... args)
    {
        return process(args...);
    }

    template <class T>
    Error process(T&& val)
    {
        return process_item(val);
    }

private:

    template <class T, class... Args>
    Error process(T&& val, Args&&... args)
    {
        Error err = process(val);
        if (err != Error::NoError) {
            return err;
        }
        process(std::forward<Args>(args)...);
        return err;
    }

    Error process_item(bool &arg)
    {
        if (arg) {
            out_ << "true" << Separator;
        } else {
            out_ << "false" << Separator;
        }
        return Error::NoError;
    }

    Error process_item(uint64_t &arg)
    {
        out_ << arg << Separator;
        return Error::NoError;
    }
};


class Deserializer
{
    static constexpr char Separator = ' ';
    std::istream& in_;

public:

    explicit Deserializer(std::istream& in)
        : in_(in)
    {
    }


    template <class T>
    Error load (T& object)
    {
        return object.deserialize(*this);
    }

    template <class... Args>
    Error operator()(Args... args)
    {
        return process(args...);
    }

    template <class T>
    Error process(T&& val)
    {
        return process_item(val);
    }

private:

    template <class T, class... Args>
    Error process(T&& val, Args&&... args)
    {
        Error err = process(val);
        if (err != Error::NoError) {
            return err;
        }
        process(std::forward<Args>(args)...);
        return err;
    }

    Error process_item(bool *value)
    {
        std::string text;
        if (!(in_ >> text)) {
            return Error::CorruptedArchive;
        }
        if (text == "true")
            *value = true;
        else if (text == "false")
            *value = false;
        else
            return Error::CorruptedArchive;
        return Error::NoError;
    }

    Error process_item(uint64_t *value)
    {
        uint64_t buf;
        if (in_ >> buf) {
            *value = buf;
            return Error::NoError;
        }
        return Error::CorruptedArchive;
    }
};
