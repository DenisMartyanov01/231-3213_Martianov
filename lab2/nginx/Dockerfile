FROM nginx:1.25-alpine

COPY templates/default.conf.template /etc/nginx/templates/
# Создаем директорию для статических файлов
RUN mkdir -p /static