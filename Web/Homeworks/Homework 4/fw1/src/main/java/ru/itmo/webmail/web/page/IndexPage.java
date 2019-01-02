package ru.itmo.webmail.web.page;

import javax.servlet.http.HttpServletRequest;
import java.util.Map;

public class IndexPage extends Page {
    private void action() {
        // No operations.
    }

    private void registrationDone(Map<String, Object> view) {
        view.put("message", "You have been registered");
    }

    private void authorizationDone(Map<String, Object> view) {
        view.put("message", "You have been authorized");
    }

    private void logoutDone(Map<String, Object> view) {
        view.put("message", "You have been logged out");
    }

    private void newsSubmitted(Map<String, Object> view) {
        view.put("message", "News successfully submitted!");
    }
}
