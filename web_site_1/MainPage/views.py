from django.contrib.auth.decorators import login_required
from django.contrib.sites.shortcuts import get_current_site
from django.http import QueryDict
from django.shortcuts import render, render_to_response, redirect, get_object_or_404, HttpResponseRedirect
from django.core.paginator import Paginator, PageNotAnInteger, EmptyPage
from django.template.loader import render_to_string
from django.utils.encoding import force_bytes, force_text
from django.utils.http import urlsafe_base64_encode, urlsafe_base64_decode
from django.contrib.auth import login, update_session_auth_hash
from django.contrib.auth.models import User
from django.contrib.auth.forms import PasswordChangeForm
from django.contrib import messages
from django.utils.text import slugify

from .forms import form_news, SignupForm, UserProfileForm, UserUpdateForm, CommentsForm
from .tokens import account_activation_token
from .models import PostComment

from django.utils.translation import ugettext_lazy as _

from .models import InfoPost

from unidecode import unidecode
import json

image_w = 100
image_h = 100

def index(request):
    if request.user.is_authenticated:
        user = User.objects.get(username=request.user.username)
        return render(request, 'MainPage/MainInfo.html', {'prof_user': user, 'img_w': image_w, 'img_h': image_h})
    return render(request, 'MainPage/MainInfo.html', {})

@login_required
def create_news(request):
    prof_form = User.objects.get(username=request.user.username)
    if request.method == "POST":
        newsf = form_news(request.POST)
        if newsf.is_valid():
            p = newsf.save(commit=False)
            p.author = request.user
            p.slug = slugify(unidecode(request.POST['title']))
            p.save()
            return redirect('post_list')
    else:
        newsf = form_news()
    return render(request, 'MainPage/NewsFormCreating.html', {"form": newsf, 'user': prof_form,'img_w': image_w, 'img_h': image_h})


def post_list(request):
    posts = InfoPost.objects.all().order_by("date")

    paginator = Paginator(posts, 5)
    page = request.GET.get('page')

    try:
        posts = paginator.page(page)
    except PageNotAnInteger:
        posts = paginator.page(1)
    except EmptyPage:
        posts = paginator.page(paginator.num_pages)

    if request.user.is_authenticated:
        user = User.objects.get(username=request.user.username)
        return render(request, "MainPage/PostList.html",
                                  {'Posts': posts, "user": user, 'img_w': image_w, 'img_h': image_h})
    return render(request, "MainPage/PostList.html", {'Posts': posts, 'img_w': image_w, 'img_h': image_h})


def info_list(request):
    posts = InfoPost.objects.all().order_by("date")
    maininfo = posts[0]
    info1 = list(InfoPost.objects.all()[1:])

    if request.user.is_authenticated:
        user = User.objects.get(username=request.user.username)
        render(request, 'MainPage/InfoList.html', {"user": user, 'img_w': image_w, 'img_h': image_h, "maininfo": maininfo, 'info1': info1})

    return render(request, 'MainPage/InfoList.html', {"maininfo": maininfo, 'info1': info1})


def post(request, slug):
    post_inst = get_object_or_404(InfoPost, slug=slug)
    q = QueryDict('', mutable=True)

    if request.method == 'POST':
        data = json.loads(request.body)

        q.update(data)
        q.update({"author":request.user, "post": post_inst})

        comment_form = CommentsForm(q)
        if comment_form.is_valid():
            com = comment_form.save(commit=False)
            com.author = request.user
            com.post = post_inst
            parent_obj = None
            try:
                parent_id = int(data['parent_id'])
            except:
                parent_id = None
            if parent_id:
                parent_qs = PostComment.objects.filter(id=parent_id)
                if parent_qs.exists() and parent_qs.count() == 1:
                    parent_obj = parent_qs.first()

            com.reply_to = parent_obj
            com.save()
            #return render(request, "MainPage/Post.html", {'comment_form': comment_form, 'post': post_inst})
            return redirect('post', slug=post_inst.slug)
    else:
        comment_form = CommentsForm()

    return render(request, 'MainPage/Post.html', {'comment_form': comment_form, 'post': post_inst,
                                                  'img_w': image_w, 'img_h': image_h})


def more(request):
    if request.user.is_authenticated:
        user = User.objects.get(username=request.user.username)
        return render(request, 'MainPage/WebPage_Info.html', {'prof_user': user})
    return render(request, 'MainPage/WebPage_Info.html')


def signup(request):
    if request.method == 'POST':
        form = SignupForm(request.POST)
        if form.is_valid():
            user = form.save(commit=False)
            user.is_active = False
            user.save()
            current_site = get_current_site(request)
            subject = 'Activate Your Account'
            message = render_to_string('MainPage/account_activation_email.html', {
                'user': user,
                'domain': current_site.domain,
                'uid': urlsafe_base64_encode(force_bytes(user.pk)).decode(),
                'token': account_activation_token.make_token(user),
            })
            user.email_user(subject, message)
            return redirect('account_activation_sent')
    else:
        form = SignupForm()

    return render(request, 'MainPage/signup.html', {'form': form})


def account_activation_sent(request):
    return render(request, 'MainPage/account_activation_sent.html')


def activate(request, uidb64, token):
    try:
        uid = urlsafe_base64_decode(uidb64).decode()
        user = User.objects.get(pk=uid)
    except (TypeError, ValueError, OverflowError, User.DoesNotExist):
        user = None

    if user is not None and account_activation_token.check_token(user, token):
        user.is_active = True
        user.profile.email_confirmed = True
        user.save()
        login(request, user)
        return redirect('index')
    else:
        return render(request, 'MainPage/account_activate_invalid.html')

def change_password(request):
    if request.method == 'POST':
        form = PasswordChangeForm(request.user, request.POST)
        if form.is_valid():
            user = form.save()
            update_session_auth_hash(request, user)
            messages.success(request, _('Your password was successfully updated!'))
            return redirect('accounts:change_password')
        else:
            messages.error(request, _('Please correct the error below.'))
    else:
        form = PasswordChangeForm(request.user)
    return render(request, 'MainPage/ChangePassword.html', {'form': form})

def user_profile(request, username):
    user = User.objects.get(username=username)
    return render(request, 'MainPage/UserProfile.html', {'user': user,'request':request, 'img_w': image_w, 'img_h': image_h})

@login_required
def edit_profile(request, username):
    if request.user.username != username:
        print("Эта страница не доступна")
        return redirect('index')
    if request.method == "POST":
        user_f = UserUpdateForm(request.POST,instance=request.user)
        p_user_f = UserProfileForm(request.POST, request.FILES, instance=request.user.profile)
        if user_f.is_valid() and p_user_f.is_valid():
            profile = p_user_f.save(commit=False)
            profile.user = request.user
            profile.save()
            return redirect('user_profile', username=username)
    else:
        user_f = UserUpdateForm(instance=request.user)
        p_user_f = UserProfileForm(instance=request.user.profile)

    return render(request, "MainPage/UserProfile_edit.html", {'u_form':user_f, 'up_form':p_user_f})
