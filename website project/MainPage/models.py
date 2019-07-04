from django.db import models
from django.db.models.signals import post_save
from django.utils import timezone
from django.contrib.auth.models import User
from django.dispatch import receiver

from tinymce.models import HTMLField
from ckeditor.fields import RichTextField

from PIL import Image


class UserProfile(models.Model):
    user = models.OneToOneField(User, on_delete=models.CASCADE, related_name='profile')

    image = models.ImageField(
        upload_to='img/',
        default='img/no-user-image.gif',
        null=True,
        blank=True,
    )
    email_confirmed = models.BooleanField(default=False)

    @receiver(post_save, sender=User)
    def update_user_profile(sender, instance, created, **kwargs):
        if created:
            UserProfile.objects.create(user=instance)
        instance.profile.save()

    def save(self, *args, **kwargs):
        super().save()

        img = Image.open(self.image.path)
        img.thumbnail((100, 100))
        img.save(self.image.path)


class InfoPost(models.Model):
    author = models.ForeignKey('auth.User', on_delete=models.CASCADE, blank=True, null=True)
    title = models.CharField(max_length=200)
    title_text = RichTextField()
    main_text = RichTextField()
    date = models.DateTimeField(auto_now_add=True)

    slug = models.SlugField(max_length=100, unique=True, default='')

    def __str__(self):
        return self.title


class PostComment(models.Model):
    post = models.ForeignKey(InfoPost, on_delete=models.CASCADE, related_name='comments')
    author = models.ForeignKey(User, on_delete=models.CASCADE, related_name="usernames")
    text = models.TextField()
    created_date = models.DateTimeField(default=timezone.now)
    #approved_comment = models.BooleanField(default=False)
    reply_to = models.ForeignKey("self", null=True, blank=True, on_delete=models.CASCADE, related_name='replies')

    #def __str__(self): return 'Comment by {} on {}'.format(self.name, self.post)

    def children(self):
        return PostComment.objects.filter(reply_to=self)

    @property
    def is_parent(self):
        if self.reply_to is not None:
            return False
        else:
            return True

    def get_all_objects(self):
        queryset = self._meta.model.objects.all()
        # can use the below method also
        # queryset = self.__class__.objects.all()
        return queryset