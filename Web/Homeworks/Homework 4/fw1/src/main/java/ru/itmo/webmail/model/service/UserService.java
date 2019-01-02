package ru.itmo.webmail.model.service;

import com.google.common.hash.Hashing;
import ru.itmo.webmail.model.domain.User;
import ru.itmo.webmail.model.exception.ValidationException;
import ru.itmo.webmail.model.repository.UserRepository;
import ru.itmo.webmail.model.repository.impl.UserRepositoryImpl;
import ru.itmo.webmail.web.exception.AuthorizationException;

import java.nio.charset.StandardCharsets;
import java.util.List;

public class UserService {
    private static final String USER_PASSWORD_SALT = "dc3475f2b301851b";

    private UserRepository userRepository = new UserRepositoryImpl();

    public void validateRegistration(User user, String email, String password, String passwordConfirmation) throws ValidationException {
        if (user.getLogin() == null || user.getLogin().isEmpty()) {
            throw new ValidationException("Login is required");
        }
        if (!user.getLogin().matches("[a-z]+")) {
            throw new ValidationException("Login can contain only lowercase Latin letters");
        }
        if (user.getLogin().length() > 8) {
            throw new ValidationException("Login can't be longer than 8");
        }
        if (userRepository.findByLogin(user.getLogin()) != null) {
            throw new ValidationException("Login is already in use");
        }

        if (!validateEmail(email)) { //
            throw new ValidationException("Invalid email");
        }

        if (password == null || password.isEmpty()) {
            throw new ValidationException("Password is required");
        }
        if (password.length() < 4) {
            throw new ValidationException("Password can't be shorter than 4");
        }
        if (password.length() > 32) {
            throw new ValidationException("Password can't be longer than 32");
        }

        if (passwordConfirmation == null || passwordConfirmation.isEmpty()) {
            throw new ValidationException("Password confirmation is required");
        }
        if (!passwordConfirmation.equals(password)) {
            throw new ValidationException("Password confirmation differs from password");
        }
    }

    private boolean validateEmail(String email) {
        return email.matches(".+@.+\\..+");
    }

    public void register(User user, String email, String password) {
        user.setPasswordSha1(getPasswordSha1(password));
        user.setId(generateId());
        user.setEmail(email);
        userRepository.save(user);
    }

    private String getPasswordSha1(String password) {
        return Hashing.sha256().hashString(USER_PASSWORD_SALT + password,
                StandardCharsets.UTF_8).toString();
    }

    public User authorize(String login, String password) throws AuthorizationException {
        User candidate = userRepository.findByLogin(login);
        if (candidate == null) {
            throw new AuthorizationException("User with this login doesn't exist!");
        }
        if (!getPasswordSha1(password).equals(candidate.getPasswordSha1())) {
            throw new AuthorizationException("Wrong password!");
        }
        return candidate;
    }

    private long generateId() {
        return findCount();
    }

    public List<User> findAll() {
        return userRepository.findAll();
    }

    public int findCount() {
        return userRepository.findCount();
    }

    public User findById(long id) {
        return userRepository.findById(id);
    }

}
