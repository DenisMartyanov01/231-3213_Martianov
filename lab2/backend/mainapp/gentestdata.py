import random, string, datetime
from .models import *
from django.db import transaction
import faker
from faker import Faker


fk = Faker()

def gentestdata():
    # try:
    with transaction.atomic():
        for i in range(1000):
            newTeacher = Teacher()
            newTeacher.name = fk.name()
            newTeacher.phone = fk.phone_number() 
            newTeacher.lesson_name = random.choice(('Английский язык', 'Информатика', 'Математика', 'Физкультура'))
            newTeacher.last_lesson = fk.date_between(
                start_date=datetime.date(2020,1,1),
                end_date=datetime.date(2024,1,1))
            newTeacher.years_of_teaching = random.randint(0, 10)
            newTeacher.is_working = random.randint(0, 1)
            newTeacher.save()

    print('OK gentestdata()')
