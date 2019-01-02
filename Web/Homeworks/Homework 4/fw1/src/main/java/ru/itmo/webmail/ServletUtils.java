package ru.itmo.webmail;

import com.google.gson.Gson;
import ru.itmo.webmail.model.domain.User;
import ru.itmo.webmail.model.service.UserService;
import ru.itmo.webmail.web.exception.AuthorizationException;

import javax.servlet.http.HttpServletRequest;
import java.util.Map;

public class ServletUtils {
    private final static Gson gson = new Gson(); // thread-safe

    public static String toJson(Object object) {
        return gson.toJson(object);
    }

    public static <T> T fromJson(String json, Class<T> type) {
        return gson.fromJson(json, type);
    }

    public static void doAuthorization(UserService userService, String login, String password, HttpServletRequest request, Map<String, Object> view) throws AuthorizationException {
        User authorized = userService.authorize(login, password);
        request.getSession().setAttribute("AuthorizedUser", authorized);
    }

    public static void doLogout(HttpServletRequest request) {
        request.getSession().removeAttribute("AuthorizedUser");
    }
}
