package ru.itmo.webmail.web.page;

import ru.itmo.webmail.ServletUtils;
import ru.itmo.webmail.model.domain.User;
import ru.itmo.webmail.model.exception.ValidationException;
import ru.itmo.webmail.web.exception.AuthorizationException;
import ru.itmo.webmail.web.exception.RedirectException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import java.rmi.server.ServerCloneException;
import java.util.Map;

public class RegisterPage extends Page {
    private void register(HttpServletRequest request, Map<String, Object> view) throws ServletException {
        User user = new User();
        user.setLogin(request.getParameter("login"));
        String email = request.getParameter("email");
        String password = request.getParameter("password");
        String passwordConfirmation = request.getParameter("passwordConfirmation");

        try {
            userService.validateRegistration(user, email, password, passwordConfirmation);
        } catch (ValidationException e) {
            view.put("login", user.getLogin());
            view.put("email", email);
            view.put("password", password);
            view.put("passwordConfirmation", passwordConfirmation);
            view.put("error", e.getMessage());
            return;
        }

        userService.register(user, email, password);
        try {
            ServletUtils.doAuthorization(userService, user.getLogin(), password, request, view);
        } catch (AuthorizationException e) {
            throw new ServletException("Couldn't authorize just registered user", e);
        }
        throw new RedirectException("/index", "registrationDone");
    }

    private void action() {
        // No operations.
    }
}
