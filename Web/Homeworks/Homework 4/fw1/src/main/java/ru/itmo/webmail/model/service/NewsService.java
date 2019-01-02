package ru.itmo.webmail.model.service;

import ru.itmo.webmail.model.domain.News;
import ru.itmo.webmail.model.domain.User;
import ru.itmo.webmail.model.repository.NewsRepository;
import ru.itmo.webmail.model.repository.impl.NewsRepositoryImpl;

import java.util.List;

public class NewsService {
    private NewsRepository newsRepository = new NewsRepositoryImpl();

    public void create(User user, String newsText) {
        newsRepository.create(user, newsText);
    }

    public List<News> findAll() {
        return newsRepository.findAll();
    }
}
