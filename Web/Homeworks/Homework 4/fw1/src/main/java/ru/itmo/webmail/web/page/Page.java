package ru.itmo.webmail.web.page;

import ru.itmo.webmail.model.domain.User;
import ru.itmo.webmail.model.service.NewsService;
import ru.itmo.webmail.model.service.UserService;

import javax.servlet.http.HttpServletRequest;
import java.util.Map;

abstract class Page {
    protected UserService userService = new UserService();
    protected NewsService newsService = new NewsService();

    void before(HttpServletRequest request, Map<String, Object> view) {
        view.put("userCount", userService.findCount());
        User user = (User) request.getSession().getAttribute("AuthorizedUser");
        if (user != null) {
            view.put("username", user.getLogin());
        } else {
            view.remove("username");
        }

        view.put("newsList", newsService.findAll());
        view.put("userService", userService);
    }

    void after(HttpServletRequest request, Map<String, Object> view) {
    }
}
