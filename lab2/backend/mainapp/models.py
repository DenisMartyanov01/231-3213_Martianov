from django.db import models


class Teacher(models.Model):
    name = models.CharField(max_length=30, null=False)
    phone = models.CharField(max_length=30, null=False)
    lesson_name = models.CharField(max_length=30, null=False)
    last_lesson = models.DateField(null=False)
    years_of_teaching = models.IntegerField(null=False)
    is_working = models.BooleanField(default=True, null=False)
    
