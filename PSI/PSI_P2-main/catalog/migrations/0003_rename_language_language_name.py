# Generated by Django 3.2.6 on 2021-09-27 17:33

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('catalog', '0002_language'),
    ]

    operations = [
        migrations.RenameField(
            model_name='language',
            old_name='language',
            new_name='name',
        ),
    ]
