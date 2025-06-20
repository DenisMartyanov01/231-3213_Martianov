"""
URL configuration for lab1 project.

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/5.2/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path, include

from mainapp.views import TeacherViewSet

urlpatterns = [
    path('admin/', admin.site.urls),
    path('api/',
         include([
            path('teacher.get', TeacherViewSet.as_view({'get': 'list'})),
            path('teacher.get/<pk>', TeacherViewSet.as_view({'get': 'retrieve'})),    
            path('teacher.create/', TeacherViewSet.as_view({'post': 'create'})),
            path('teacher.delete/<pk>', TeacherViewSet.as_view({'get': 'destroy'})),
            path('teacher.update/<pk>', TeacherViewSet.as_view({'post': 'update'}))
         ]))
]
