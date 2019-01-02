package ru.itmo.webmail.web.exception;

public class AuthorizationException extends Exception {
    public AuthorizationException(String message) {
        super(message);
    }
}
