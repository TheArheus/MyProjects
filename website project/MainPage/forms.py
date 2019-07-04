import itertools

from django import forms
from django.core.files.images import get_image_dimensions
from django.contrib.auth.forms import UserCreationForm
from .models import InfoPost, User, UserProfile, PostComment

from ckeditor.widgets import CKEditorWidget


class form_news(forms.ModelForm):
    title = forms.CharField()

    title_text = forms.CharField(widget=CKEditorWidget(attrs={'height': '40', 'width':'20'}))
    main_text = forms.CharField(widget=CKEditorWidget(attrs={'height': "80", 'width': "40"}))

    slug = forms.CharField(required=False)

    class Meta:
        model = InfoPost
        fields = ['title', 'title_text', 'main_text', 'slug', 'author']

    """
    def save(self):
        instance = super(form_news, self).save(commit=False)

        max_length = InfoPost._meta.get_field('slug').max_length
        instance.slug = orig = slugify(instance.title)[:max_length]

        for x in itertools.count(1):
            if not InfoPost.objects.filter(slug=instance.slug).exists():
                break

            # Truncate the original slug dynamically. Minus 1 for the hyphen.
            instance.slug = "%s-%d" % (orig[:max_length - len(str(x)) - 1], x)

        instance.save()
        return instance
    """

    """
    def clean_author(self):
        if not self.cleaned_data['author']:
            return User()
        return self.cleaned_data['author']
    """

    title.widget.attrs.update({"class": "form-control", "cols":"1"})
    slug.widget.attrs.update({'id': 'slug', "class": "form-control", 'type':'hidden'})


class SignupForm(UserCreationForm):
    email = forms.EmailField(max_length=254, help_text='Required. Inform a valid email address.')

    class Meta:
        model = User
        fields = ('username', 'email', 'password1', 'password2')


class UserProfileForm(forms.ModelForm):
    user = forms.CharField(required=False)

    class Meta:
        model = UserProfile
        fields = '__all__'

    def clean_avatar(self):
        avatar = self.cleaned_data['avatar']

        try:
            w, h = get_image_dimensions(avatar)

            #validate dimensions
            max_width = max_height = 100
            if w > max_width or h > max_height:
                raise forms.ValidationError(
                    u'Please use an image that is '
                     '%s x %s pixels or smaller.' % (max_width, max_height))

            #validate content type
            main, sub = avatar.content_type.split('/')
            if not (main == 'image' and sub in ['jpeg', 'pjpeg', 'gif', 'png']):
                raise forms.ValidationError(u'Please use a JPEG, '
                    'GIF or PNG image.')

            #validate file size
            if len(avatar) > (20 * 1024):
                raise forms.ValidationError(
                    u'Avatar file size may not exceed 20k.')

        except AttributeError:
            #Handles case when we are updating the user profile
            #and do not supply a new avatar
            pass

        return avatar

class UserUpdateForm(forms.ModelForm):
    email = forms.EmailField(required=False)
    username = forms.CharField(required=False)

    class Meta:
        model = User
        fields = ['username', 'email']


class CommentsForm(forms.ModelForm):
    created_date = forms.DateTimeField(required=False)

    class Meta:
        model = PostComment
        exclude = ("post", "author", "created_date",)
        fields = '__all__'
